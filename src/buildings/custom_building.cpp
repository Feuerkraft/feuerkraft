//  $Id: custom_building.cpp,v 1.9 2003/06/23 08:43:32 grumbel Exp $
//
//  Feuerkraft - A Tank Battle Game
//  Copyright (C) 2002 Ingo Ruhnke <grumbel@gmx.de>
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

#include "../alist.hpp"
#include "../resource_manager.hpp"
#include "custom_building.hpp"

CustomBuilding::CustomBuilding(const AList& type, const AList& lst)
  : Building(lst)
{
  std::string sprite_str = "feuerkraft/nobuilding";
  int         i_energie = 100;
  width   = 2;
  height  = 2;

  type.retrieve_string("sprite",  sprite_str);
  type.retrieve_int   ("energie", i_energie);
  type.retrieve_int   ("width",   width);
  type.retrieve_int   ("height",  height);

  energie.set_max_energie(i_energie);

  sprite = resources->get_sprite(sprite_str);
}

void
CustomBuilding::draw(View& view)
{
  view.get_sc().color().draw(sprite,
                     x_pos * 40 + get_map_width()*20, 
                     y_pos * 40 + get_map_height()*20); // FIXME: Hardcoded tilesize
}

void
CustomBuilding::draw_energie(View& view)
{
  energie.draw(view, x_pos*40 + get_map_width()*20, (y_pos*40));
}

void
CustomBuilding::update(float)
{
}

void
CustomBuilding::collide (Projectile*)
{
  energie -= 5;
}

/* EOF */
