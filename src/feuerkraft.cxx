//  $Id: feuerkraft.cxx,v 1.47 2003/06/06 14:25:47 grumbel Exp $
// 
//  Feuerkraft - A Tank Battle Game
//  Copyright (C) 2000 Ingo Ruhnke <grumbel@gmx.de>
//
//  This program is free software; you can redistribute it and/or
//  modify it under the terms of the GNU General Public License
//  as published by the Free Software Foundation; either version 2
//  of the License, or (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
// 
//  You should have received a copy of the GNU General Public License
//  along with this program; if not, write to the Free Software
//  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

#include <config.h>
#include <iostream>
#include <ClanLib/gl.h>
#include <ClanLib/GL/setupgl.h>
#include <ClanLib/core.h>
#include <libguile.h>

#include <time.h>

#include "feuerkraft.hxx"
#include "game_world.hxx"
#include "keyboard_manager.hxx"
#include "fonts.hxx"
#include "math.hxx"
#include "player_view.hxx"
#include "display_manager.hxx"

// GameObjs
#include "tank.hxx"
#include "ai_vehicle.hxx"
#include "robot_tank.hxx"
#include "jeep.hxx"
#include "tree.hxx"
#include "helicopter.hxx"
#include "soldier.hxx"
#include "background.hxx"

#include "system.hxx"

#include "path_manager.hxx"
#include "ambulance.hxx"
#include "menu.hxx"
#include "handle_manager.hxx"
#include "menu_item.hxx"
#include "start_screen.hxx"
#include "sound/sound.hxx"
#include "collision_manager.hxx"
#include "command_line_arguments.hxx"

#include "particles/explosion_particle.hxx"

#include "groundmap/ground_map.hxx"
#include "groundmap/ground_map_data.hxx"
#include "groundmap/ground_map_data_factory.hxx"

#include "buildings/building_map_data.hxx"
#include "buildings/building_map.hxx"
#include "buildings/building_type_manager.hxx"

#include "resource_manager.hxx"
#include "game_obj_factory.hxx"
#include "property_set.hxx"
#include "property.hxx"

#include "input/input_manager.hxx"
#include "globals.hxx"
#include "output_world_builder.hxx"
#include "sexpr_world_reader.hxx"
#include "player.hxx"
#include "guile.hxx"

// FIXME: Replace this with a PlayerManager class or something similar
Player*  player;

//#define WITH_STATIC_READLINE 1

#ifdef WITH_STATIC_READLINE
extern "C" void scm_init_readline();
#endif
extern "C" void SWIG_init(void);
          
void inner_main (void* closure, int argc, char* argv[]);

// Global Instance of the main class
Feuerkraft feuerkraft;

void 
Feuerkraft::init()
{
  // Init Guile
  scm_init_guile ();
  Guile::enable_debug();
  Guile::enable_readline();

  // Init Swig
  SWIG_init();

  // Init ClanLib
  CL_SetupCore::init();
  CL_SetupDisplay::init();
  CL_SetupGL::init();

  // Init Sound Subsystem
  music_enabled = args->music_enabled;
  sound_enabled = args->sound_enabled;
  PingusSound::init();

  // Init pseudo random number generator
  srand (time (0));

  // Find the location of Feuerkrafts data files (images, sounds, etc.) 
  if (args->datadir.empty())
    {
      path_manager.add_path("../data");
      path_manager.add_path("data");
      path_manager.add_path("share/games/feuerkraft");
      path_manager.add_path("../share/games/feuerkraft");
            
      path_manager.find_path("feuerkraft.xml");
    }
  else
    {
      path_manager.set_path(args->datadir);
    }

  // Create the main window
  window = new CL_DisplayWindow(PACKAGE_STRING, args->screen_width, args->screen_height);
  CL_Display::set_current_window (window);
  CL_Display::clear();

  resources = new ResourceManager ();
  Fonts::init();

  // Load helper functions
  scm_c_primitive_load(path_manager.complete("feuerkraft.scm").c_str());

  KeyboardManager::instance();
  InputManager::init();
}

Feuerkraft::Feuerkraft()
{
  args = 0;
}

Feuerkraft::~Feuerkraft()
{
  delete args;
}
	
int
Feuerkraft::main(int argc, char** argv)
{
  // Make arguments accessible for all member functions
  args = new CommandLineArguments(argc, argv);

  // Create a console window for text-output if not available
  CL_ConsoleWindow console("Console");
  console.redirect_stdio();
  
  // Init all subsystems
  init();

  try
    {
      BuildingTypeManager buildingtypemanager;


      CollisionManager collision_mgr;

      // Deserialize the game world
      GameWorld* world;
      {
        std::cout << "<<<<<<<<<<<<< Parsing map <<<<<<<<<<<<<" << std::endl;
        if (args->mission_file.empty())
          args->mission_file = path_manager.complete("missions/airport.feu");

        SCM fdes = scm_open_file (scm_makfrom0str(args->mission_file.c_str()), 
                                  scm_makfrom0str("r"));
        SCM lst  = scm_read (fdes);

        OutputWorldBuilder builder;
        SexprWorldReader(lst, &builder).run();

        GameWorldData data(lst);
        world = new GameWorld (lst);

        scm_close (fdes);

        std::cout << ">>>>>>>>>>>>> Parsing map >>>>>>>>>>>>>" << std::endl;
      }
      // End: Test of parsing code
        
      Tank* tank1 = new Tank(FloatVector2d (560, 1245), 5, 
                             "feuerkraft/tank2", "feuerkraft/turret2", "feuerkraft/fire2");

      AIVehicle* ai_vehicle = new AIVehicle(FloatVector2d(342, 1241));

      GameObj* tree = GameObjFactory::instance()->create(1, AList()
                                                         .set_float("x-pos", 50.0f)
                                                         .set_float("y-pos", 50.0f)
                                                         .set_string("sprite", "feuerkraft/tree"));
      world->add(tree);
      RobotTank* robot_tank = new RobotTank(660, 1245, 0, 100.0f);
      world->add(robot_tank);

      Soldier* soldier = new Soldier(FloatVector2d (500, 1100));

      Player the_player(soldier);
      player = &the_player;
      View view(0, 0, CL_Display::get_width(), CL_Display::get_height(),
                new PlayerViewUpdater(player));
      //View view2(400, 0, 800, 600, new VehicleViewUpdater(ai_vehicle));

      world->add(new Helicopter(FloatVector2d(600, 1245)));

      world->add(new Tank(FloatVector2d (450, 1245), 5, 
                          "feuerkraft/tank", "feuerkraft/turret", "feuerkraft/fire2"));
      
      for(int x = 15; x < 25; x += 3)
        world->add(new Tank(FloatVector2d (x*40 - 20, 54*40), 5, 
                            "feuerkraft/tank2", "feuerkraft/turret2", "feuerkraft/fire2"));

      world->add(tank1);
      world->add(ai_vehicle);

      world->add(new Background (resources->get_sprite("feuerkraft/sand"), -10.0f));
      world->add(new Ambulance());

      world->add(soldier);
	
      /** 1/30sec = 1.0delta
       */
      float delta;
      unsigned int last_time = CL_System::get_time ();

      int loops = 0;
      float deltas = 0.0;

      int start_time = CL_System::get_time ();
      int frames = 0;

      CL_System::keep_alive();

      int delta_wait = static_cast<int>(1000/args->fps);

      CL_System::keep_alive();
      DisplayManager::init();

      // Loop until the user hits escape:
      while (!CL_Keyboard::get_keycode(CL_KEY_ESCAPE)) //start_screen.logo_mode != StartScreen::S_QUIT)
        {
          // Poor mans pause button
          if (CL_Keyboard::get_keycode(CL_KEY_P))
            {
              while (CL_Keyboard::get_keycode(CL_KEY_P))
                CL_System::keep_alive();

              while (!CL_Keyboard::get_keycode(CL_KEY_P))
                CL_System::keep_alive();

              while (CL_Keyboard::get_keycode(CL_KEY_P))
                CL_System::keep_alive();

              last_time = CL_System::get_time ();
            }

          if (CL_Keyboard::get_keycode(CL_KEY_D))
            Guile::enter_repl();

          /* Switch between hard and variable updates here */
          //delta = ((CL_System::get_time () - last_time) / 1000.0f);
          delta = delta_wait/1000.0f;

          last_time = CL_System::get_time ();

          collision_mgr.clear();
          world->update (delta);
          collision_mgr.run();
	    
          deltas += delta;
          ++loops;

          view.update(delta);
          //view2.update(delta);

          // Clip Rectangle
          //window.get_gc()->set_cliprect(CL_Rect(5, 5, 395, 595));
          
          GameWorld::current()->draw(view);
          GameWorld::current()->draw_energie(view);
          collision_mgr.draw(view);

          //window.get_gc()->set_cliprect(CL_Rect(405, 5, 795, 595));
          //GameWorld::current()->draw(view2);
          //GameWorld::current()->draw_energie(view2);

          DisplayManager::current()->update(delta);
          DisplayManager::current()->draw(*(CL_Display::get_current_window()->get_gc()));

          if (CL_Mouse::get_keycode(CL_MOUSE_MIDDLE))
            world->add(new ExplosionParticle(view.screen_to_world(FloatVector2d(CL_Mouse::get_x (),
                                                                                CL_Mouse::get_y ())),
                                             FloatVector2d(), 3.0f));

          if (CL_Mouse::get_keycode(CL_MOUSE_RIGHT))
            ai_vehicle->clear_orders();
            
          if (CL_Mouse::get_keycode(CL_MOUSE_LEFT))
            {
              while (CL_Mouse::get_keycode(CL_MOUSE_LEFT))
                CL_System::keep_alive ();

              FloatVector2d pos (view.screen_to_world (FloatVector2d(CL_Mouse::get_x (), CL_Mouse::get_y ())));

              std::cout << "Mouse: " <<  pos << " | "
                        << world->get_groundmap ()->get_groundtype (pos.x, pos.y) 
                        << " | " <<  int(pos.x) / 40  << " " << int(pos.y) / 40
                        << std::endl;

              ai_vehicle->drive_to(pos);
            }
	    
          // Comment out for variable frame rate
          int sleep_time = (last_time + delta_wait) - CL_System::get_time();
          if (sleep_time > 0)
            CL_System::sleep (sleep_time);

          if (CL_Keyboard::get_keycode(CL_KEY_M))
            {
              DisplayManager::current()->show_levelmap();
            }

          //start_screen.draw ();
          //start_screen.update (delta);

          // Flip front and backbuffer. This makes the changes visible:
          CL_Display::flip ();
          //window.get_gc()->clear ();
          ++frames;
	    
          // Update keyboard input and handle system events:
          // Exits the loop if ClanLib requests shutdown - for instance if
          // someone closes the window.
          CL_System::keep_alive();
          InputManager::update(delta);
          // FIXME: Add an input dispatcher here, depending on the
          // dispatcher state, input should go to the menu, to the
          // comm-dialog or to the players vehicle
          if (DisplayManager::current()->get_menu())
            {
              DisplayManager::current()->get_menu()->process_events(InputManager::get_events());
            }
          else
            {
              player->get_current_unit()->update_controlls(InputManager::get_events());
            }
        }
      DisplayManager::deinit();

      std::cout << "Avarage delta: " << deltas/loops << std::endl;
      std::cout << "Avarage fps:   " 
                << float (frames) / (CL_System::get_time () - start_time) * 1000.0 << std::endl;

      Fonts::deinit();
      PingusSound::deinit();
      CL_SetupGL::deinit();
      CL_SetupDisplay::deinit();
      CL_SetupCore::deinit();
    }
  catch (CL_Error err)
    {
      std::cout << "CL_Error: " << err.message.c_str() << std::endl;
    }
  catch (...)
    {
      std::cout << "Something catched..." << std::endl;
    }

  // Display console close message and wait for a key
  console.display_close_message();

  return 0;
}

// EOF //
