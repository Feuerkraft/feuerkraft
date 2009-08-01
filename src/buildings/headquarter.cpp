//  $Id: headquarter.cpp,v 1.9 2003/06/22 19:22:56 grumbel Exp $
//
//  Feuerkraft - A Tank Battle Game
//  Copyright (C) 2000 Ingo Ruhnke <grumbel@gmx.de>
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//  
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//  
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include "../radar.hpp"
#include "../explosion.hpp"
#include "../resource_manager.hpp"
#include "headquarter.hpp"

Headquarter::Headquarter (const AList& lst)
  : Building (lst),
    pos (x_pos * 40 + 40, y_pos * 40 + 40),
    headquarter (resources->get_sprite("feuerkraft/headquarter")),
    headquarter_damaged (resources->get_sprite("feuerkraft/headquarterdamaged")),
    headquarter_destroyed (resources->get_sprite("feuerkraft/headquarterdestroyed")),
    energie (100),
    destroyed (false)
{
  current_sur = &headquarter;
}

Headquarter::~Headquarter ()
{
}

void 
Headquarter::update (float delta)
{
  if (energie <= 0 && !destroyed)
    {
      GameWorld::current()->add(new Explosion (pos, Explosion::MEDIUM));
      destroyed = true;
    }
}

void 
Headquarter::draw (View& view)
{
  view.get_sc().color().draw(*current_sur, pos.x, pos.y);
  energie.draw (view, int(pos.x), int(pos.y - 40));
}

void
Headquarter::draw_radar (Radar& radar)
{
  radar.draw_blip (pos, 4);
}

bool 
Headquarter::is_colliding (FloatVector2d obj_pos)
{
  return (!destroyed &&
	  obj_pos.x > pos.x - 40 && obj_pos.x < pos.x + 40 &&
	  obj_pos.y > pos.y - 40 && obj_pos.y < pos.y + 40);
}

void 
Headquarter::collide (Projectile*)
{
  energie -= 10;

  if (energie > 60)
    current_sur = &headquarter;
  else if (energie > 0)
    current_sur = &headquarter_damaged;
  else
    current_sur = &headquarter_destroyed;
}

bool
Headquarter::alive ()
{
  return (energie > 0);
}

/* EOF */
