//  $Id: Jeep.cc,v 1.1 2001/02/24 20:32:12 grumbel Exp $
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

#include "Jeep.hh"

extern CL_ResourceManager* resources;

Jeep::Jeep (CL_Vector arg_pos) :
  jeep ("feuerkraft/jeep", resources),
  energie (50),
  velocity (0.0),
  angle (0.0),
  flag (0)
{
  pos = arg_pos;
}

void 
Jeep::update (float delta)
{
  CL_Vector vel (-velocity, 0.0, 0.0);
  
  pos += vel.rotate (angle, CL_Vector (0.0, 0.0, 1.0)) * delta;

  velocity /= 1.03f;

  if (flag)
    {
      CL_Vector flag_offset (14.0, 0.0, 0.0);
      flag->set_pos (pos
		     + flag_offset.rotate (angle, CL_Vector (0.0, 0.0, 1.0)));
    }
}

void 
Jeep::draw (View* view)
{
  const float circle = 6.2831854f;
  int frame = (int(fmod(angle, circle) / circle * jeep.get_num_frames ()) + 16) % 16;

  jeep.put_screen (view->get_x_offset () + 
		   pos.x - jeep.get_width ()/2,
		   view->get_y_offset () + 
		   pos.y - jeep.get_height ()/2,
		   frame);
  energie.draw (view, pos.x, pos.y - 30);
}

void 
Jeep::turn_left (float delta)
{
  angle += 0.06f * (velocity/5) * delta;
}

void 
Jeep::turn_right (float delta)
{
  angle -= 0.06f * (velocity/5) * delta;
}

void 
Jeep::turn_left2 (float delta) 
{
}

void
Jeep::turn_right2 (float delta) 
{
}

void
Jeep::increase_velocity (float delta)
{
  velocity += 0.25f * delta;
}

void
Jeep::decrease_velocity (float delta)
{
  velocity -= 0.25f * delta;
}

void
Jeep::start_fire () 
{
}

void
Jeep::stop_fire () 
{
}

void
Jeep::drop_mine () 
{
}

void 
Jeep::collide (Projectile*)
{
  energie -= 5;
}

void 
Jeep::collide (Mine*)
{
  energie -= 25;
}

void 
Jeep::collide (CL_Vector force) 
{
  energie -= int(force.norm ());
  
  std::cout << "Jeep: Got force: " << force.norm () << std::endl;
}

bool 
Jeep::is_colliding (CL_Vector obj_pos)
{
  float range = 6.0; 

  return  (obj_pos.x > pos.x - range && obj_pos.x < pos.x + range
	   && obj_pos.y > pos.y - range && obj_pos.y < pos.y + range);
}

void 
Jeep::add_flag (Flag* f)
{
  flag = f;
}

/* EOF */
