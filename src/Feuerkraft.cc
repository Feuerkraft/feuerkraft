/*
	Loads a single surface from a pcx file without using resource files.
*/

#include <ClanLib/png.h>
#include <ClanLib/core.h>


#include "GameWorld.hh"
#include "KeyboardController.hh"
#include "JoystickController.hh"
#include "Tank.hh"
#include "Tree.hh"
#include "Helicopter.hh"
#include "Turret.hh"
#include "Tower.hh"
#include "Soldier.hh"

CL_ResourceManager* resources;

class Feuerkraft : public CL_ClanApplication
{
public:
  virtual char *get_title() { return "Surface application"; }
	
  CL_Surface load_surface()
  {
    return CL_Surface(new CL_PCXProvider("survivor.pcx", NULL), true);
  }
	
  virtual int main(int argc, char** argv)
  {
    try
      {
	srand (time (0));

	float sec_fraction = 33.0;
	if (argc == 3)
	  {
	    if (strcmp (argv[1], "--speed") == 0
		&& sscanf (argv[2], "%f", &sec_fraction) == 1)
	      {

	      }
	    else
	      {
		std::cout << "Wrong args: " << argv[1] << " " << argv[2] << std::endl;
	      }
	  }

		std::cout << "New Fraction Time: " << sec_fraction << std::endl;

	CL_SetupCore::init();
	CL_SetupCore::init_display();
	CL_SetupPNG::init ();

	// Set mode: 320x200 16 bpp
	CL_Display::set_videomode(800, 600, 16, false);
	CL_Display::clear_display (0.7f, 0.7f, 0.6f);
	CL_Display::flip_display ();
		
	resources =  CL_ResourceManager::create("data/feuerkraft.scr", false);

	GameWorld world;

	Tank* tank1 = new Tank(5, "feuerkraft/tank", "feuerkraft/turret", "feuerkraft/fire");
	Tank* tank2 = new Tank(5, "feuerkraft/tank2", "feuerkraft/turret2", "feuerkraft/fire2");
	Helicopter* heli = new Helicopter (CL_Vector (320, 200));

	JoystickController controller(heli);
	KeyboardController kcontroller (tank2);

	world.add (heli);
	world.add (tank1);
	world.add (tank2);
	world.add (new Tower (400.0, 200.0));
	world.add (new Tower (600.0, 400.0));
	world.add (new Tower (600.0, 100.0));

	world.add (new Tree (CL_Vector (100, 400), "feuerkraft/tree"));
	world.add (new Tree (CL_Vector (400, 440), "feuerkraft/tree"));
	world.add (new Tree (CL_Vector (400, 440), "feuerkraft/tree"));

	world.add (new Soldier (CL_Vector (200, 200)));
	world.add (new Soldier (CL_Vector (300, 300)));
	world.add (new Soldier (CL_Vector (150, 400)));
	world.add (new Soldier (CL_Vector (550, 400)));
	world.add (new Soldier (CL_Vector (550, 100)));

	/** 1/30sec = 1.0delta
	 */
	float delta;
	int last_time = CL_System::get_time ();

	int loops = 0;
	float deltas = 0.0;
	
	// Loop until the user hits escape:
	while (CL_Keyboard::get_keycode(CL_KEY_ESCAPE) == false)
	  {	
	    delta = (CL_System::get_time () - last_time) / sec_fraction;
	    last_time = CL_System::get_time ();
	    world.update (delta);
	    
	    deltas += delta;
	    ++loops;

	    CL_Display::clear_display (0.7f, 0.7f, 0.6f);
	    
	    world.draw ();
	    
	    controller.update (delta);
	    kcontroller.update (delta);

	    // Flip front and backbuffer. This makes the changes visible:
	    CL_Display::flip_display();
	    
	    // Update keyboard input and handle system events:
	    // Exits the loop if ClanLib requests shutdown - for instance if
	    // someone closes the window.
	    CL_System::keep_alive();
	  }

	std::cout << "Avarage delta: " << deltas/loops << std::endl;

	CL_SetupPNG::deinit ();
	CL_SetupCore::deinit_display();
	CL_SetupCore::deinit();
      }
    catch (CL_Error err)
      {
	std::cout << "CL_Error: " << err.message.c_str() << std::endl;
      }

    return 0;
  }
} feuerkraft;

  // EOF 
