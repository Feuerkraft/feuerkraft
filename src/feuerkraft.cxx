/*
	Loads a single surface from a pcx file without using resource files.
*/

#include <iostream>
#include <ClanLib/GL/setupgl.h>
#include <ClanLib/core.h>
#include <ClanLib/application.h>
#include <libguile.h>

#include <time.h>

#include "feuerkraft.hxx"
#include "game_world.hxx"
#include "keyboard_controller.hxx"
#include "keyboard_manager.hxx"
#include "tank.hxx"
#include "ai_vehicle.hxx"
#include "robot_tank.hxx"
#include "jeep.hxx"
#include "fonts.hxx"
#include "tree.hxx"
#include "math.hxx"
#include "helicopter.hxx"
#include "turret.hxx"
#include "soldier.hxx"
#include "player_view.hxx"
#include "vehicle_status.hxx"
#include "radar.hxx"
#include "screen.hxx"
#include "background.hxx"
#include "system.hxx"
#include "path_manager.hxx"
#include "ambulance.hxx"
#include "level_map.hxx"
#include "start_screen.hxx"
#include "sound/sound.hxx"
#include "collision_manager.hxx"
#include "command_line_arguments.hxx"

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

class Feuerkraft : public CL_ClanApplication
{
public:
  virtual char *get_title() { return "Feuerkraft 0.2.0"; }

  virtual int main(int argc, char** argv)
  {
    try {
      scm_boot_guile (argc, argv,::inner_main, 0);
    } catch (...) {
      std::cout << "Feuerkraft: catched something" << std::endl;
    }
    return 0;
  }
	
  virtual int inner_main(void* closure, int argc, char** argv)
  {
    SWIG_init();

    // Create a console window for text-output if not available
    CL_ConsoleWindow console("Console");
    console.redirect_stdio();

    try
      {
        CommandLineArguments args(argc, argv);
        
	srand (time (0));

        if (args.datadir.empty())
          {
            path_manager.add_path("../data");
            path_manager.add_path("data");
            path_manager.add_path("share/games/feuerkraft");
            path_manager.add_path("../share/games/feuerkraft");
            
            path_manager.find_path("feuerkraft.xml");
          }
        else
          {
            path_manager.set_path(args.datadir);
          }

	CL_SetupCore::init();
	//CL_SetupSound::init();
	CL_SetupDisplay::init();
	CL_SetupGL::init();
        
        music_enabled = args.music_enabled;
        sound_enabled = args.sound_enabled;

        PingusSound::init();
        
	//CL_OpenGL::begin_2d();
	CL_DisplayWindow window("Feuerkraft", 800, 600);

	CL_Display::set_current_window (&window);
	window.get_gc()->clear();

	resources = new ResourceManager ();
        //Fonts::init();

        Guile::enable_debug();
        Guile::enable_readline();

        // Load helper functions
        scm_c_primitive_load(path_manager.complete("feuerkraft.scm").c_str());

        KeyboardManager::instance();
        BuildingTypeManager buildingtypemanager;
        Screen    screen;

        CollisionManager collision_mgr;

        // Deserialize the game world
	GameWorld* world;
	{
	  std::cout << "<<<<<<<<<<<<< Parsing map <<<<<<<<<<<<<" << std::endl;
          if (args.mission_file.empty())
            args.mission_file = path_manager.complete("missions/airport.feu");

	  SCM fdes = scm_open_file (scm_makfrom0str(args.mission_file.c_str()), 
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

	Vehicle* current_vehicle = tank1;
	Controllable* current_controllable = tank1;
	KeyboardController kcontroller(current_controllable);

        GameObj* tree = GameObjFactory::instance()->create(1, AList()
                                                           .set_float("x-pos", 50.0f)
                                                           .set_float("y-pos", 50.0f)
                                                           .set_string("sprite", "feuerkraft/tree"));
	world->add(tree);
        RobotTank* robot_tank = new RobotTank(660, 1245, 0, 100.0f);
        world->add(robot_tank);

        Player the_player(tank1);
        player = &the_player;
	View view(0, 0, 800, 600, new PlayerViewUpdater(player));
	//View view2(400, 0, 800, 600, new VehicleViewUpdater(ai_vehicle));
       
        screen.add(new Radar(FloatVector2d(64, 64), player));
	screen.add(new VehicleStatus(current_vehicle));

	world->add(tank1);
	world->add(ai_vehicle);

	world->add(new Background (resources->get_sprite("feuerkraft/sand"), -10.0f));
	world->add(new Ambulance());

	world->add(new Soldier(FloatVector2d (200, 200)));
	world->add(new Soldier(FloatVector2d (300, 300)));
	world->add(new Soldier(FloatVector2d (150, 400)));
	world->add(new Soldier(FloatVector2d (550, 400)));
	world->add(new Soldier(FloatVector2d (550, 100)));
	
	/** 1/30sec = 1.0delta
	 */
	float delta;
	unsigned int last_time = CL_System::get_time ();

	int loops = 0;
	float deltas = 0.0;

	int start_time = CL_System::get_time ();
	int frames = 0;

	CL_System::keep_alive();

	int delta_wait = static_cast<int>(1000/args.fps);

	LevelMap levelmap;
	

        CL_System::keep_alive();

	// Loop until the user hits escape:
	while (!CL_Keyboard::get_keycode(CL_KEY_ESCAPE)) //start_screen.logo_mode != StartScreen::S_QUIT)
	  {
	    // Poor mans pause button
	    if (window.get_ic()->get_keyboard().get_keycode(CL_KEY_P))
	      {
		while (window.get_ic()->get_keyboard().get_keycode(CL_KEY_P))
		  CL_System::keep_alive();
		while (!window.get_ic()->get_keyboard().get_keycode(CL_KEY_P))
		  CL_System::keep_alive();
		while (window.get_ic()->get_keyboard().get_keycode(CL_KEY_P))
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

	    screen.update (delta);
	    screen.draw(window.get_gc ());

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
	    
	    kcontroller.update (delta);
	    
	    // Comment out for variable frame rate
	    int sleep_time = (last_time + delta_wait) - CL_System::get_time();
	    if (sleep_time > 0)
	      CL_System::sleep (sleep_time);

	    if (window.get_ic()->get_keyboard().get_keycode(CL_KEY_M))
	      {
		levelmap.draw (window.get_gc ());
	      }

	    //start_screen.draw ();
	    //start_screen.update (delta);

            //Fonts::font.draw(10, 10, "Hello World");

	    // Flip front and backbuffer. This makes the changes visible:
	    window.flip ();
	    //window.get_gc()->clear ();
	    ++frames;
	    
	    // Update keyboard input and handle system events:
	    // Exits the loop if ClanLib requests shutdown - for instance if
	    // someone closes the window.
	    CL_System::keep_alive();
	  }

	std::cout << "Avarage delta: " << deltas/loops << std::endl;
	std::cout << "Avarage fps:   " 
		  << float (frames) / (CL_System::get_time () - start_time) * 1000.0 << std::endl;

        //Fonts::deinit();
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
} feuerkraft;

// Wrapper to call the member func
void inner_main (void* closure, int argc, char* argv[])
{
  feuerkraft.inner_main (closure, argc, argv);
}

// EOF 
