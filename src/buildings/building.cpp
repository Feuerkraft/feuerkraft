//  $Id: building.cpp,v 1.6 2003/08/20 00:02:46 grumbel Exp $
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

#include "../property_set.hpp"
#include "../radar.hpp"
#include "building.hpp"

Building::Building (const AList& lst) :
  id(),
  properties(),
  x_pos (lst.get_int("x-pos")),
  y_pos (lst.get_int("y-pos"))
{
  register_properties();
}

Building::~Building ()
{
  delete properties;
}

void
Building::register_properties()
{
  properties = new PropertySet();

  properties->register_int("x-pos", &x_pos);
  properties->register_int("y-pos", &y_pos);
}

void
Building::draw_radar(Radar& radar)
{
  radar.draw_blip(FloatVector2d(x_pos * 40, y_pos * 40), 3, .5f, .5f, .5f);
}

/* EOF */
