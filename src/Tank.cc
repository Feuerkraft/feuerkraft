#include <iostream>
#include <string>
#include <ClanLib/core.h>

#include "Turret.hh"
#include "Tank.hh"

const float circle = 6.2831854;
extern CL_ResourceManager* resources;

Tank::Tank (int reloading_speed, std::string tank, std::string turret, std::string fire) : 
  angle (0.0),
  speed (0.0),
  velocity (0.0),
  x_pos (rand () % 80 +100),
  y_pos (rand () % 80 + 300),
  increment (0.06),
  inc_step (0),
  sur (tank.c_str (), resources),
  smod ("feuerkraft/smod", resources),
  turret (new Turret(this, reloading_speed, turret, fire)),
  smod_step (0)
{
}

Tank::~Tank ()
{
  delete turret;
}
  
void
Tank::draw ()
{
  int frame = int(fmod (angle, circle) / circle * 16.0);
  
  for (std::deque<CL_Vector>::iterator i = smodpos.begin ();
       i != smodpos.end (); ++i)
    {
      smod.put_screen (i->x - (smod.get_width ()/2),
		       i->y - (smod.get_height ()/2), 
		       int(fmod (i->z, circle) / circle * 16.0));
    }

  sur.put_screen (int(x_pos) - (sur.get_width ()/2),
		  int(y_pos) - (sur.get_height ()/2),
		  frame);
  turret->draw ();
}

void 
Tank::update ()
{
  turret->set_world (world);
  turret->update ();

  if (velocity > 0.06)
    velocity -= 0.05;
  else if (velocity < -0.06)
    velocity += 0.05;
  else
    velocity = 0;

  if (velocity > 1)
    velocity = 1.0;
  else if (velocity < -1)
    velocity = -1.0;

  CL_Vector pos (x_pos, y_pos);
  CL_Vector vel (-velocity, 0.0);
  //std::cout << "Angle: " << angle 
  //	    << " CAngle: " << angle - fmod(angle, circle/16) 
  //	    << " Mod: " << fmod (angle, circle/16.0) << std::endl;
  vel = vel.rotate (angle - fmod(angle, circle/16.0), CL_Vector (0.0, 0.0, 1.0));

  if (velocity != 0.0 || tmp_angle != angle)
    {
      if (smod_step++ > 50)
	{
	  smod_step = 0;
	  tmp_angle = angle;
	  smodpos.push_back (CL_Vector (x_pos, y_pos, angle));
	  if (smodpos.size () > 20)
	    smodpos.pop_front ();
	}
    }

  pos = pos + vel;
  x_pos = pos.x;
  y_pos = pos.y;
}

void 
Tank::increase_angle ()
{
  if (velocity >= 0)
    angle += increment;
  else
    angle += increment;
  angle = fmod (angle + circle, circle);
}

void
Tank::decrease_angle ()
{
  if (velocity >= 0)
    angle -= increment;
  else
    angle -= increment;
  angle = fmod (angle + circle, circle);
}

void
Tank::set_angle (float arg_angle)
{
  angle = angle;
}

void 
Tank::increase_velocity ()
{
  velocity += 0.1;
}

void
Tank::decrease_velocity ()
{
  velocity -= 0.1;
}

void 
Tank::start_fire ()
{
  turret->start_fire ();
}

void 
Tank::stop_fire ()
{
  turret->stop_fire ();
}

// EOF //

