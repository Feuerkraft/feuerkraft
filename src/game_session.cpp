//  $Id: game_session.cpp,v 1.6 2003/06/23 09:04:10 grumbel Exp $
//
//  Pingus - A free Lemmings clone
//  Copyright (C) 2002 Ingo Ruhnke <grumbel@gmx.de>
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include <ClanLib/Core/System/system.h>
#include <ClanLib/Display/display.h>
#include <ClanLib/Display/display_window.h>
#include <ClanLib/Display/mouse.h>
#include <ClanLib/Display/keyboard.h>
#include <ClanLib/Display/keys.h>
#include <sstream>
#include <iostream>
#include <assert.h>

#include "globals.hpp"
#include "particles/explosion_particle.hpp"
#include "menu.hpp"
#include "groundmap/ground_map.hpp"
#include "player_view.hpp"
#include "input/input_manager.hpp"
#include "soldier.hpp"
#include "game_obj_factory.hpp"

#include "vehicles/tank.hpp"
#include "vehicles/helicopter.hpp"

#include "background.hpp"
#include "robot_tank.hpp"
#include "view.hpp"
#include "display_manager.hpp"
#include "buildings/building_type_manager.hpp"
#include "scripting/clanlib_commands.hpp"
#include "scripting/menu_commands.hpp"
#include "collision_manager.hpp"
#include "sexpr_world_reader.hpp"
#include "guile.hpp"
#include "soldier_ai.hpp"
#include "ai_manager.hpp"
#include "ai_vehicle.hpp"
#include "vehicle_ai.hpp"
#include "output_world_builder.hpp"
#include "game_world.hpp"
#include "player.hpp"
#include "path_manager.hpp"
#include "command_line_arguments.hpp"
#include "screenshot.hpp"
#include "game_session.hpp"

// FIXME: Replace this with a PlayerManager class or something similar
Player*  player;

GameSession::GameSession(const std::string& arg_filename) :
  control_state(UNIT_CONTROL),
  filename(arg_filename),
  do_quit(false),
  do_pause(false),
  deltas(),
  loops(),
  frames(),
  start_time(),
  buildingtypemanager(),
  collision_mgr(),
  world(),
  view()
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

  // Load helper functions
  // FIXME: These functions need a better place
  scm_c_primitive_load(path_manager.complete("feuerkraft.scm").c_str());
  scm_c_primitive_load(path_manager.complete("input.scm").c_str());

  // Deserialize the game world
  {
    std::cout << "<<<<<<<<<<<<< Parsing map <<<<<<<<<<<<<" << std::endl;
    SCM fdes = scm_open_file (scm_makfrom0str(filename.c_str()),
                              scm_makfrom0str("r"));
    SCM lst = scm_read (fdes);
    scm_close (fdes);

    // unstable Testing stuff
    //OutputWorldBuilder builder;
    //SexprWorldReader(lst, &builder).run();

    // Now we create the real world
    world = new GameWorld(lst);
    std::cout << ">>>>>>>>>>>>> Parsing map >>>>>>>>>>>>>" << std::endl;
  }
  // End: Test of parsing code

  // The all mighty soldier that the player controlls
  Soldier* soldier = new Soldier(AList());
  soldier->set_position(FloatVector2d (500, 1100));

  {
    Soldier* soldier = new Soldier(AList());
    soldier->set_position(FloatVector2d (1400, 1500));
    SoldierAI* ai = new SoldierAI(soldier);
    world->add(soldier);
    AIManager::instance()->add(ai);
  }

  {
    Soldier* soldier = new Soldier(AList());
    soldier->set_position(FloatVector2d (1300, 1600));
    SoldierAI* ai = new SoldierAI(soldier);
    world->add(soldier);
    AIManager::instance()->add(ai);
  }

  world->add(new RobotTank(660, 1245, 0, 100.0f));
  world->add(new Helicopter(AList()
                            .set_float("x-pos", 600)
                            .set_float("y-pos", 1245)
                            .set_int("type", 0)));
  world->add(new Helicopter(AList()
                            .set_float("x-pos", 600)
                            .set_float("y-pos", 1445)
                            .set_int("type", 1)));
  world->add(new Helicopter(AList()
                            .set_float("x-pos", 660)
                            .set_float("y-pos", 1645)
                            .set_int("type", 2)));

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
  view->get_sc().render();
  view->get_sc().light().fill_screen(CL_Color(50, 50, 100));

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

  if (!args->video_record_directory.empty())
    {
      std::stringstream filename;
      filename << args->video_record_directory;
      filename.width(8);
      filename.fill('0');
      filename << frames;
      filename << ".ppm";
      Screenshot::write_screenshot_pnm(filename.str());
    }

  ++frames;

  // Update keyboard input and handle system events:
  // Exits the loop if ClanLib requests shutdown - for instance if
  // someone closes the window.
  CL_System::keep_alive();
  clanlib_call_post_keep_alive_func();
  InputManager::update(delta);

  InputEventLst lst = InputManager::get_controller().get_events();
  for(InputEventLst::iterator i = lst.begin(); i != lst.end(); ++i)
    {
      if (i->type == BUTTON_EVENT)
        {
          if (i->button.name == MENU_BUTTON && i->button.is_down())
            {
              if (control_state == MENU_CONTROL)
                {
                  menu_hide();
                  control_state = UNIT_CONTROL;
                }
              else
                {
                  menu_show(0);
                  control_state = MENU_CONTROL;
                }
            }
          else if (i->button.name == USE_BUTTON && i->button.is_down())
            {
              // FIXME: Unclean hack
              gh_call0(gh_lookup("join-nearest-vehicle"));
            }
        }
    }

  switch (control_state)
    {
    case MENU_CONTROL:
      if (DisplayManager::current()->get_menu())
        DisplayManager::current()->get_menu()->process_events(InputManager::get_controller().get_events());
      else
        {
          std::cout << "Error: Menu not available, fallback to unit" << std::endl;
          control_state = UNIT_CONTROL;
        }
      break;

    case UNIT_CONTROL:
      player->get_current_unit()->update_controlls(InputManager::get_controller());
      break;

    default:
      std::cout << "Unknown ControlState, switching back to UNIT_CONTROL" << std::endl;
      control_state = UNIT_CONTROL;
      break;
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
