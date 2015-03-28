//  $Id: unit.cpp,v 1.5 2003/08/20 00:02:46 grumbel Exp $
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

#include "property_set.hpp"
#include "player.hpp"
#include "radar.hpp"
#include "unit.hpp"

extern Player* player;

Unit::Unit() :
  pos(),
  orientation()
{
  pos = FloatVector2d(0,0);
  orientation = 0;

  properties->register_float("x-pos", &pos.x);
  properties->register_float("y-pos", &pos.y);

  properties->register_float("orientation", &orientation);
}

Unit::~Unit()
{
}

void
Unit::draw_radar(Radar& radar)
{
  if (player->get_current_unit() != this)
    radar.draw_blip(pos, 2, 1.0f, 0, 0);
}

void
Unit::set_position(const FloatVector2d& new_pos)
{
  pos = new_pos;
}

void
Unit::set_orientation(float new_orientation)
{
  orientation = new_orientation;
}

/* EOF */
