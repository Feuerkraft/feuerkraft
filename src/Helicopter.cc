//  $Id: Helicopter.cc,v 1.3 2001/02/20 22:49:01 grumbel Exp $
//
//  Pingus - A free Lemmings clone
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

#include "Explosion.hh"
#include "Helicopter.hh"

extern CL_ResourceManager* resources;

Helicopter::Helicopter (CL_Vector arg_pos) :
  rotor ("feuerkraft/rotor", resources),
  heli ("feuerkraft/helicopter", resources),
  helidestroyed ("feuerkraft/helidestroyed", resources),
  pos (arg_pos),
  rotor_count (0),
  velocity (0.0),
  angle (0.0),
  strafe (0.0),
  fireing (false),
  energie (100),
  destroyed (false)
{
}

Helicopter::~Helicopter ()
{
}

void 
Helicopter::draw ()
{
  if (!destroyed)
    {
      const float circle = 6.2831854f;
      int frame = (int(fmod(angle, circle) / circle * heli.get_num_frames ()) + 16) % 16;
      //std::cout << "angle: " << angle << std::endl;
  
      heli.put_screen (pos.x - heli.get_width ()/2,
		       pos.y - heli.get_height ()/2,
		       frame);
      rotor.put_screen (pos.x - rotor.get_width ()/2,
			pos.y - rotor.get_height ()/2,
			(rotor_count = (rotor_count + 1) % 2));
      energie.draw (pos.x, pos.y - 40);
    }
  else
    {
      helidestroyed.put_screen (pos.x - helidestroyed.get_width ()/2,
				pos.y - helidestroyed.get_height ()/2);
    }
}

void 
Helicopter::update (float delta)
{
  if (energie <= 0 && !destroyed)
    {
      world->add (new Explosion (pos, Explosion::MEDIUM));
      destroyed = true;
    }

  CL_Vector vel (-velocity, 0.0, 0.0);

  pos += vel.rotate (angle, CL_Vector (0.0, 0.0, 1.0)) * delta;
  pos += CL_Vector (0.0, strafe, 0.0).rotate (angle, CL_Vector (0.0, 0.0, 1.0)) * delta;

  velocity /= 1.03f;
  strafe /= 1.03f;

  if (fireing && !reloading)
    {
      float rot_angle = angle + 3.1415927;
      CL_Vector dir = CL_Vector (15.0, 0.0).rotate (rot_angle, CL_Vector (0.0, 0.0, 1.0));
      world->add (new Projectile (pos
				  + CL_Vector (0.0, -5.0, 0.0).rotate (rot_angle, CL_Vector (0.0, 0.0, 1.0)),
				  dir));
      reloading = 4;
    }

  if (reloading)
    --reloading;
}

void 
Helicopter::increase_velocity ()
{
  velocity += 0.1f;
}

void 
Helicopter::decrease_velocity ()
{
  velocity -= 0.1f;
}

void
Helicopter::turn_left ()
{
  angle += 0.04f;
}

void 
Helicopter::turn_right ()
{
  angle -= 0.04f;
}

void 
Helicopter::turn_left2 ()
{
  strafe -= 0.1f;
}

void 
Helicopter::turn_right2 ()
{
  strafe += 0.1f;
}

void
Helicopter::start_fire () 
{
  fireing = true;  
}

void 
Helicopter::stop_fire () 
{
  fireing = false;
}

bool 
Helicopter::is_colliding (CL_Vector obj_pos)
{
  float range = 20.0; 

  return  (obj_pos.x > pos.x - range && obj_pos.x < pos.x + range
	   && obj_pos.y > pos.y - range && obj_pos.y < pos.y + range);
}

void
Helicopter::collide (Projectile*) 
{
  energie -= 15;
}

/* EOF */
