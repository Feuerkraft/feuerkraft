//  $Id: Tower.cc,v 1.9 2001/11/28 17:17:27 grumbel Exp $
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

Tower::Tower (boost::dummy_ptr<GameWorld>  w,
	      float arg_x_pos, float arg_y_pos) 
  : Vehicle (w),
    towerbase ("feuerkraft/towerbase", resources),
    towerdamaged ("feuerkraft/towerdamaged", resources),
    towerdestroyed ("feuerkraft/towerdestroyed", resources),
    turret ("feuerkraft/towerturret", resources),
    fireing (true),
    angle (0),
    energie (100),
    destroyed (false)
{
  pos = CL_Vector (arg_x_pos, arg_y_pos);
}

void
Tower::draw (View* view) 
{
  if (energie > 50)
    {
      view->draw (towerbase,
		  int(pos.x) - towerbase.get_width ()/2,
		  int(pos.y) - towerbase.get_height ()/2);
    }
  else if (energie > 0)
    {
      view->draw (towerdamaged,
		  int(pos.x) - towerdamaged.get_width ()/2,
		  int(pos.y) - towerdamaged.get_height ()/2);
    }
  else
    {
      view->draw (towerdestroyed,
		  int(pos.x) - towerdestroyed.get_width ()/2,
		  int(pos.y) - towerdestroyed.get_height ()/2);
    }

  if (!destroyed)
    {
      view->draw (turret, 
		  int(pos.x) - turret.get_width ()/2, 
		  int(pos.y) - turret.get_height ()/2);
      energie.draw (view,
		    int(pos.x), int (pos.y) - 40);
    }

  /*
  view->draw_rect (int(pos.x) - 40, int(pos.y) - 40, 
		   int(pos.x) + 40, int(pos.y) + 40, 
		   1.0f, 1.0f, 1.0f);*/
}

void
Tower::update (float delta) 
{
  if (destroyed)
    return;

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
      world->add (new Explosion (world, pos, Explosion::MEDIUM));
      destroyed = true;
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
  float range = 36.0;
  if (!destroyed)
    return (obj_pos.x > pos.x - range && obj_pos.x < pos.x + range
	    && obj_pos.y > pos.y - range && obj_pos.y < pos.y + range);
  else
    return false;
}

void 
Tower::collide (Projectile* projectile)
{
  energie -= 5;
}

/* EOF */
