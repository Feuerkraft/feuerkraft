/*
	Loads a single surface from a pcx file without using resource files.
*/

#include <iostream>
#include <ClanLib/GL/setupgl.h>
#include <ClanLib/core.h>
#include <ClanLib/application.h>
//#include <ClanLib/sound.h>
#include <libguile.h>

#include <time.h>

#include "feuerkraft.hxx"
#include "game_world.hxx"
#include "keyboard_controller.hxx"
//#include "joystick_controller.hxx"
#include "tank.hxx"
#include "ai_vehicle.hxx"
#include "jeep.hxx"
#include "tree.hxx"
#include "math.hxx"
#include "flag.hxx"
#include "helicopter.hxx"
#include "turret.hxx"
#include "playfield.hxx"
#include "soldier.hxx"
#include "vehicle_view.hxx"
#include "vehicle_status.hxx"
#include "radar.hxx"
#include "screen.hxx"
#include "background.hxx"
#include "stone.hxx"
#include "system.hxx"
#include "path_manager.hxx"
#include "ambulance.hxx"
#include "level_map.hxx"
#include "start_screen.hxx"
#include "line_segments.hxx"
#include "sound/sound.hxx"
#include "collision_manager.hxx"
#include "command_line_arguments.hxx"

#include "groundmap/ground_map.hxx"
#include "groundmap/ground_map_data.hxx"
#include "groundmap/ground_map_data_factory.hxx"

#include "buildings/building_map_data.hxx"
#include "buildings/building_map.hxx"
#include "generic/ofstreamext.hxx"
#include "resource_manager.hxx"
#include "guile.hxx"

// FIXME: Ugly global variable, should be removed as soon as possible
VehicleView* vehicle_view;

//FIXME: Another ugly global variable, should be removed as soon as possible
CL_GraphicContext* global_gc;

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
            path_manager.add_path("..");
            path_manager.add_path(".");
            
            path_manager.find_path("data/feuerkraft.xml");
          }
        else
          {
            path_manager.set_path(args.datadir);
          }

	CL_SetupCore::init();
	//CL_SetupSound::init();
	CL_SetupDisplay::init();
	CL_SetupGL::init();

        PingusSound::init();
        
	resources = new ResourceManager ();

	//CL_OpenGL::begin_2d();
	CL_DisplayWindow window("Feuerkraft", 800, 600);

	CL_Display::set_current_window (&window);
	global_gc = window.get_gc();
	window.get_gc()->clear();

	std::cout << "Trying load and destroy of a sprite" << std::endl;
	resources->get_sprite("feuerkraft/tank2_shadow");
	std::cout << "End: Trying load and destroy of a sprite" << std::endl;
        
        // Deserialize the game world
	GameWorld* world;
	{
	  std::cout << "<<<<<<<<<<<<< Parsing map <<<<<<<<<<<<<" << std::endl;
	  SCM fdes = scm_open_file (scm_makfrom0str("data/missions/test.feu"), 
                                    scm_makfrom0str("r"));
	  SCM lst  = scm_read (fdes);

	  GameWorldData data(lst);
	  world = new GameWorld (lst);

	  scm_close (fdes);

	  std::cout << ">>>>>>>>>>>>> Parsing map >>>>>>>>>>>>>" << std::endl;
	}
	// End: Test of parsing code
        
        // Load helper functions
        scm_c_primitive_load("src/scripting/feuerkraft.scm");

        // Load game scripts 
        scm_c_primitive_load("data/missions/test.scm");

	Screen    screen;

	Tank* tank2 = new Tank(world, CL_Vector (800, 200), 5,
                               "feuerkraft/tank", "feuerkraft/turret", "feuerkraft/fire");
	Tank* tank1 = new Tank(world, CL_Vector (560, 1245), 5, 
                               "feuerkraft/tank2", "feuerkraft/turret2", "feuerkraft/fire2");
        AIVehicle* ai_vehicle = new AIVehicle(world, CL_Vector(342, 1241));

	Helicopter* heli = new Helicopter (world, CL_Vector (320, 200));
	//Helicopter* heli2 = new Helicopter (CL_Vector (320, 200));
	Jeep* jeep = new Jeep (world, CL_Vector (250, 250));

	Vehicle* current_vehicle = tank1;
	Controllable* current_controllable = tank1;

	KeyboardController kcontroller (&window, current_controllable);
	//JoystickController controller(heli);

	//Radar radar1 (CL_Vector(800-64, 64), 
	//world, tank1);

	//Radar radar2 (CL_Vector(64, 64), 
	//world, tank2);

        CollisionManager collision_mgr;

	boost::shared_ptr<GuiObj> radar 
	  = boost::shared_ptr<GuiObj>(new Radar (CL_Vector(64, 64), 
						 world, current_vehicle));
	screen.add (radar);
	screen.add (boost::shared_ptr<GuiObj>(new VehicleStatus (current_vehicle)));
	//View view (world, 10, 10, 790, 590);

	world->add (jeep);
	world->add (heli);
	//world->add (heli2);
	world->add (tank1);
	world->add (ai_vehicle);
	world->add (tank2);
	world->add (new Background (world, resources->get_sprite("feuerkraft/sand"), -10.0f));
	//world->add (new Background (world, resources->get_sprite("feuerkraft/cloudshadow"), 150.0f));
	world->add (new Playfield (world));
	world->add (new Flag (world, CL_Vector(200.0f, 200.f)));

	world->add (new Ambulance (world));
	
	for (int i = 0; i < 20; ++i)
	  {
	    world->add (new Stone (world, CL_Vector (rand () % 2048 - 1024,
						     rand () % 2048 - 1024)));
	  }

	world->add(new Soldier (world, CL_Vector (200, 200)));
	world->add(new Soldier (world, CL_Vector (300, 300)));
	world->add(new Soldier (world, CL_Vector (150, 400)));
	world->add(new Soldier (world, CL_Vector (550, 400)));
	world->add(new Soldier (world, CL_Vector (550, 100)));
	
	/** 1/30sec = 1.0delta
	 */
	float delta;
	unsigned int last_time = CL_System::get_time ();

	int loops = 0;
	float deltas = 0.0;

	VehicleView view (world, current_vehicle, 0, 0, 800, 600, window.get_gc ());

	view.set_zoom (0.5f);
	view.set_view (400, 300);

	vehicle_view = &view;
	
	//VehicleView view1 (world, heli, 0, 0, 399, 600);
	//VehicleView view2 (world, current_vehicle, 400, 0, 800, 600);
	
	int start_time = CL_System::get_time ();
	int frames = 0;

	CL_System::keep_alive();

	int delta_wait = static_cast<int>(1000/args.fps);

	LevelMap levelmap (world);
	

        CL_System::keep_alive();

        LineSegments segments(560, 1245, 3.14159f);
        CL_Vector last_pos(560, 1245);
        segments.add_straight_segment(last_pos.x, last_pos.y, last_pos.x, last_pos.y);

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

	    /* Switch between hard and variable updates here */
	    //delta = ((CL_System::get_time () - last_time) / 1000.0f);
	    delta = delta_wait/1000.0f;

	    last_time = CL_System::get_time ();

	    view.update (delta);

            collision_mgr.clear();
	    world->update (delta);
            collision_mgr.run();
	    
	    deltas += delta;
	    ++loops;

	    view.draw (window.get_gc ());
            segments.draw(&view);
            collision_mgr.draw(&view);

	    screen.update (delta);
	    screen.draw (window.get_gc ());

	    if (CL_Mouse::get_keycode(CL_MOUSE_RIGHT))
              ai_vehicle->clear_orders();
            
	    if (CL_Mouse::get_keycode(CL_MOUSE_LEFT))
	      {
		while (CL_Mouse::get_keycode(CL_MOUSE_LEFT))
		  CL_System::keep_alive ();

		CL_Vector pos (view.screen_to_world (CL_Vector(CL_Mouse::get_x (), CL_Mouse::get_y ())));

		std::cout << "Mouse: " <<  pos << " | "
			  << world->get_groundmap ()->get_groundtype (pos.x, pos.y) 
			  << " | " <<  int(pos.x) / 40  << " " << int(pos.y) / 40
			  << std::endl;

                ai_vehicle->drive_to(pos);

                //segments.add_straight_segment(last_pos.x, last_pos.y, pos.x, pos.y);
                segments.add_controll_point(pos.x, pos.y, 50);
                last_pos = pos;
	      }
	    
	    //controller.update (delta);
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
