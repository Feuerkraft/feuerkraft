//  $Id: jeep.cxx,v 1.6 2003/06/03 14:11:22 grumbel Exp $
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

#include <ClanLib/gl.h>
#include <iostream>
#include "buildings/building_map.hxx"
#include "jeep.hxx"
#include "resource_manager.hxx"

const float circle = 6.2831854f;

Jeep::Jeep(FloatVector2d arg_pos) 
  : energie (50),
    velocity (0.0),
    angle (0.0)
{
  pos.x = arg_pos.x;
  pos.y = arg_pos.y;
  jeep = resources->get_sprite ("feuerkraft/jeep");
}

void 
Jeep::update (float delta)
{
  delta *= 50;

  FloatVector2d tmp_pos = pos + FloatVector2d(-velocity, 0.0).rotate(angle) * delta;

  if (!(GameWorld::current()->get_buildingmap ()->get_building (FloatVector2d(pos.x, tmp_pos.y))))
    {
      pos.y = tmp_pos.y;
    }
  else
    {
      //velocity /= delta;
    }

  if (!(GameWorld::current()->get_buildingmap ()->get_building (FloatVector2d(tmp_pos.x, pos.y))))
    {
      pos.x = tmp_pos.x;
    }
  else
    {
      //velocity /= delta;
    }


  velocity /= 1.03f;
}

void 
Jeep::draw (View& view)
{
  const float circle = 6.2831854f;
  
  view.draw(jeep, pos, angle/(circle/2.0)*180);
  energie.draw (view, int(pos.x), int(pos.y - 30));
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
Jeep::collide (FloatVector2d force) 
{
  energie -= int(force.get_length());
  
  std::cout << "Jeep: Got force: " << force.get_length() << std::endl;
}

bool 
Jeep::is_colliding (FloatVector2d obj_pos)
{
  float range = 6.0; 

  return  (obj_pos.x > pos.x - range && obj_pos.x < pos.x + range
	   && obj_pos.y > pos.y - range && obj_pos.y < pos.y + range);
}

/* EOF */
