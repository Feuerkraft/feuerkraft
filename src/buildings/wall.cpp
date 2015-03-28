//  $Id: wall.cpp,v 1.9 2003/06/23 09:56:39 grumbel Exp $
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

#include "../property_set.hpp"
#include "../radar.hpp"
#include "../view.hpp"
#include "../resource_manager.hpp"
#include "wall.hpp"

Wall::Wall (const AList& lst)
  : Building(lst),
    pos (x_pos * 40 + 20, y_pos * 40 + 20),
    wall (resources->get_sprite("feuerkraft/wall")),
    wall_damaged (resources->get_sprite ("feuerkraft/wall_damaged")),
    wall_destroyed (resources->get_sprite ("feuerkraft/wall_destroyed")),
    energie()
{
  energie = lst.get_int("energie", 100);
  properties->register_int("energie", &energie);
}

Wall::~Wall ()
{
}

void
Wall::draw (View& view)
{
  if (energie > 60)
    view.get_sc().color().draw (wall, pos.x, pos.y);
  else if (energie > 0)
    view.get_sc().color().draw (wall_damaged, pos.x, pos.y);
  else
    view.get_sc().color().draw (wall_destroyed, pos.x, pos.y);
}

void
Wall::draw_radar (Radar& radar)
{
  radar.draw_blip (pos, 2);
}

void
Wall::update(float)
{
}

void
Wall::collide (Projectile*)
{
  energie -= 25;
}

bool
Wall::alive ()
{
  return energie > 0;
}

/* EOF */
