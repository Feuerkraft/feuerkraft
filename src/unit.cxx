//  $Id: unit.cxx,v 1.2 2003/06/04 13:10:09 grumbel Exp $
//
//  Feuerkraft - A Tank Battle Game
//  Copyright (C) 2002 Ingo Ruhnke <grumbel@gmx.de>
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

#include "property_set.hxx"
#include "unit.hxx"

Unit::Unit()
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
Unit::set_position(const FloatVector2d& new_pos)
{
  
}

void
Unit::set_orientation(float new_orientation)
{
}

/* EOF */
