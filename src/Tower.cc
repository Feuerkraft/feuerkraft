//  $Id: Tower.cc,v 1.1 2001/02/17 20:02:11 grumbel Exp $
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
#include "Projectile.hh"
#include "Tower.hh"

void
Tower::draw () 
{
  towerbase.put_screen (int(pos.x) - towerbase.get_width ()/2,
			int(pos.y) - towerbase.get_height ()/2);
  turret.put_screen (int(pos.x) - turret.get_width ()/2, 
		     int(pos.y) - turret.get_height ()/2, angle/10);
  energie.draw (int(pos.x), int (pos.y) - 40);
}

void
Tower::update () 
{
  if (++angle >= 160)
    angle = 0;

  /*
  if (angle % 10 == 0)
    {
      CL_Vector dir = CL_Vector(10.0, 0.0).rotate (angle, CL_Vector (0.0, 0.0, 1.0));
      world->add (new Projectile (pos + CL_Vector (0.0, -5.0, 0.0).rotate (angle, CL_Vector (0.0, 0.0, 1.0)),
				  dir));
				  }*/

  if (energie <= 0)
    {
      world->add (new Explosion (pos, Explosion::MEDIUM));
      remove ();
    }
}

void
Tower::start_fire () 
{
}

void
Tower::stop_fire () 
{
}

bool 
Tower::is_colliding (CL_Vector obj_pos)
{
  return (obj_pos.x > pos.x - 30.0 && obj_pos.x < pos.x + 30.0
	  && obj_pos.y > pos.y - 30.0 && obj_pos.y < pos.y + 30.0);
}

void 
Tower::collide (Projectile* projectile)
{
  energie -= 5;
  std::cout << "Energie: " << energie << std::endl;
  projectile->detonate ();
  
}

/* EOF */
