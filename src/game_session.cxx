//  $Id: game_session.cxx,v 1.2 2003/06/18 21:43:50 grumbel Exp $
//
//  Pingus - A free Lemmings clone
//  Copyright (C) 2002 Ingo Ruhnke <grumbel@gmx.de>
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

#include <ClanLib/Core/System/system.h>
#include <ClanLib/Display/display.h>
#include <ClanLib/Display/display_window.h>
#include <ClanLib/Display/mouse.h>
#include <ClanLib/Display/keyboard.h>
#include <ClanLib/Display/keys.h>
#include <iostream>
#include <assert.h>

#include "globals.hxx"
#include "particles/explosion_particle.hxx"
#include "menu.hxx"
#include "groundmap/ground_map.hxx"
#include "player_view.hxx"
#include "input/input_manager.hxx"
#include "soldier.hxx"
#include "game_obj_factory.hxx"
#include "tank.hxx"
#include "helicopter.hxx"
#include "background.hxx"
#include "robot_tank.hxx"
#include "view.hxx"
#include "display_manager.hxx"
#include "buildings/building_type_manager.hxx"
#include "collision_manager.hxx"
#include "sexpr_world_reader.hxx"
#include "guile.hxx"
#include "soldier_ai.hxx"
#include "ai_manager.hxx"
#include "ai_vehicle.hxx"
#include "vehicle_ai.hxx"
#include "output_world_builder.hxx"
#include "game_world.hxx"
#include "player.hxx"
#include "command_line_arguments.hxx"
#include "game_session.hxx"

// FIXME: Replace this with a PlayerManager class or something similar
Player*  player;
extern CommandLineArguments* args;

GameSession::GameSession(const std::string& arg_filename)
  : filename(arg_filename),
    do_quit(false),
    do_pause(false)
{  
}

void
GameSession::init()
{
  loops = 0;
  deltas = 0.0;

  start_time = CL_System::get_time ();
  frames = 0;

  collision_mgr       = new CollisionManager();
  buildingtypemanager = new BuildingTypeManager();
  
  // Deserialize the game world
  {
    std::cout << "<<<<<<<<<<<<< Parsing map <<<<<<<<<<<<<" << std::endl;
    SCM fdes = scm_open_file (scm_makfrom0str(filename.c_str()), 
                              scm_makfrom0str("r"));
    SCM lst = scm_read (fdes);
    scm_close (fdes);

    OutputWorldBuilder builder;
    SexprWorldReader(lst, &builder).run();

    GameWorldData data(lst);
    world = new GameWorld (lst);
    std::cout << ">>>>>>>>>>>>> Parsing map >>>>>>>>>>>>>" << std::endl;
  }
  // End: Test of parsing code

  // The all mighty soldier that the player controlls
  Soldier* soldier = new Soldier();
  soldier->set_position(FloatVector2d (500, 1100));

  {
    Soldier* soldier = new Soldier();
    soldier->set_position(FloatVector2d (1400, 1500));
    SoldierAI* ai = new SoldierAI(soldier);
    world->add(soldier);
    AIManager::instance()->add(ai);
  }

  {
    Soldier* soldier = new Soldier();
    soldier->set_position(FloatVector2d (1300, 1600));
    SoldierAI* ai = new SoldierAI(soldier);
    world->add(soldier);
    AIManager::instance()->add(ai);
  }

  world->add(new RobotTank(660, 1245, 0, 100.0f));
  world->add(new Helicopter(FloatVector2d(600, 1245)));

  world->add(new Tank(FloatVector2d (650, 1245), 5, "feuerkraft/tank", "feuerkraft/turret", "feuerkraft/fire2"));
  world->add(new Tank(FloatVector2d (750, 1245), 5, "feuerkraft/tank", "feuerkraft/turret", "feuerkraft/fire2"));
  world->add(new Tank(FloatVector2d (850, 1245), 5, "feuerkraft/tank", "feuerkraft/turret", "feuerkraft/fire2"));

  {
    Tank* tank = new Tank(FloatVector2d (450, 1245), 5, "feuerkraft/tank", "feuerkraft/turret", "feuerkraft/fire2");
    world->add(tank);
    AIManager::instance()->add(new VehicleRoboAI(tank));
  }

  {
    Tank* tank = new Tank(FloatVector2d (0, 1245), 5, "feuerkraft/tank2", "feuerkraft/turret", "feuerkraft/fire2");
    world->add(tank);
    AIManager::instance()->add(new VehicleRoboAI(tank));
  }

  {
    Tank* tank = new Tank(FloatVector2d (-100, 1245), 5, "feuerkraft/tank", "feuerkraft/turret2", "feuerkraft/fire2");
    world->add(tank);
    AIManager::instance()->add(new VehicleRoboAI(tank));
  }

  {
    Tank* tank = new Tank(FloatVector2d (560, 1245), 5, "feuerkraft/tank2", "feuerkraft/turret2", "feuerkraft/fire2");
    world->add(tank);
    VehiclePathAI* ai = new VehiclePathAI(tank);

    ai->drive_to(FloatVector2d(200, 200));
    ai->drive_to(FloatVector2d(500, 200));
    ai->drive_to(FloatVector2d(500, 500));
    ai->drive_to(FloatVector2d(1500, 500));
    ai->drive_to(FloatVector2d(1500, 300));

    AIManager::instance()->add(ai);
  }

  world->add(new Background (resources->get_sprite("feuerkraft/sand"), -10.0f));
  world->add(soldier);

  player = new Player(soldier);
  view   = new View(0, 0, CL_Display::get_width(), CL_Display::get_height(), new PlayerViewUpdater(player));
  DisplayManager::init();
}

void 
GameSession::update()
{
  int delta_wait = static_cast<int>(1000/args->fps);
  float delta = delta_wait/1000.0f;;

  deltas += delta;
  ++loops;

  if (CL_Keyboard::get_keycode(CL_KEY_D))
    Guile::enter_repl();

  unsigned int last_time = CL_System::get_time ();

  // Update stuff
  if (!do_pause)
    {
      collision_mgr->clear();
      AIManager::instance()->update(delta);
      world->update(delta);
      collision_mgr->run();
      view->update(delta);
    }

  GameWorld::current()->draw(*view);
  GameWorld::current()->draw_energie(*view);

  if (draw_colmap)
    collision_mgr->draw(*view);

  if (!do_pause)
    DisplayManager::current()->update(delta);
      
  DisplayManager::current()->draw(*(CL_Display::get_current_window()->get_gc()));

  if (CL_Mouse::get_keycode(CL_MOUSE_MIDDLE))
    world->add(new ExplosionParticle(view->screen_to_world(FloatVector2d(CL_Mouse::get_x (),
                                                                         CL_Mouse::get_y ())),
                                     FloatVector2d(), 3.0f));

  // Comment out for variable frame rate
  int sleep_time = (last_time + delta_wait) - CL_System::get_time();
  if (sleep_time > 0)
    CL_System::sleep (sleep_time);

  // Flip front and backbuffer. This makes the changes visible:
  CL_Display::flip ();
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
      player->get_current_unit()->update_controlls(InputManager::get_controller());
    }
  InputManager::clear();
}

void
GameSession::deinit()
{
  delete world;
  delete buildingtypemanager;
  delete collision_mgr;

  DisplayManager::deinit();

  std::cout << "Avarage delta: " << deltas/loops << std::endl;
  std::cout << "Avarage fps:   " 
            << float (frames) / (CL_System::get_time () - start_time) * 1000.0 << std::endl;
}

void
GameSession::pause()
{
  do_pause = !do_pause;
}

void
GameSession::save(const std::string& arg_filename)
{
}

/* EOF */
