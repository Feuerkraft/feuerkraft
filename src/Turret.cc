#include <iostream>
#include "Projectile.hh"
#include "Tank.hh"
#include "Turret.hh"

extern CL_ResourceManager* resources;

const float circle = 6.2831854f;

Turret::Turret (Tank* arg_tank, int r_speed, std::string surface, std::string fire) :
  sur (surface.c_str (), resources),
  fire_sur (fire.c_str (), resources),
  fireing (false),
  reloading (0),
  reloading_speed (r_speed)
{
  tank = arg_tank;
}

Turret::~Turret ()
{
}

void 
Turret::draw ()
{
  float absolute_angle = tank->get_angle () + angle;
  int frame = int(fmod (absolute_angle, circle) / circle * 16.0);
  
  sur.put_screen (tank->get_pos ().x - (sur.get_width ()/2), 
		  tank->get_pos ().y - (sur.get_height ()/2),
		  frame);

  if (fireing && reloading == 0)
    {
      fire_sur.put_screen (tank->get_pos ().x - (fire_sur.get_width ()/2), 
			   tank->get_pos ().y - (fire_sur.get_height ()/2),
			   frame);
      fireing = false;
      reloading = reloading_speed;
    }
}

void
Turret::update (float delta)
{

  static bool floppy;

  if (reloading)
    reloading--;

  if (fireing && reloading == 0)
    {
      //std::cout << "Fireing..." << std::endl;
      float rot_angle = tank->get_angle () + angle + 3.1415927 - fmod(angle, circle/16.0);
      
      CL_Vector dir = CL_Vector (10.0, 0.0).rotate (rot_angle, CL_Vector (0.0, 0.0, 1.0));

      if (floppy)
	{
	  world->add (new Projectile (tank->get_pos ()
				      + CL_Vector (0.0, -5.0, 0.0).rotate (rot_angle, CL_Vector (0.0, 0.0, 1.0)),
				      dir));
	}
      else
	{
	  world->add (new Projectile (tank->get_pos ()
				  + CL_Vector (0.0, 5.0, 0.0).rotate (rot_angle, CL_Vector (0.0, 0.0, 1.0)),
				      dir));
	}
      floppy = !floppy;
    }
}

void 
Turret::increase_angle (float delta)
{
  angle += tank->get_increment () * delta;
  angle = fmod (angle + circle, circle);
}

void
Turret::decrease_angle (float delta)
{
  angle -= tank->get_increment ();
  angle = fmod (angle + circle, circle);
}

void
Turret::start_fire ()
{
  fireing = true;
}

void
Turret::stop_fire ()
{
  fireing = false;
}

void 
Turret::set_angle (float arg_angle)
{
  angle = arg_angle;
}

// EOF 
