//  $Id: pathfinder.hpp,v 1.7 2003/06/03 14:11:22 grumbel Exp $
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

#ifndef HEADER_PATHFINDER_HXX
#define HEADER_PATHFINDER_HXX

#include <math.h>

// Datatypes shared by all the pathfinder 

enum { PARENT_NONE = 0, //!< Parent isn't set
       PARENT_GOAL,  //!< This is the goal node, it doesn't have a parent
       PARENT_NORTH, //!< parent is in north direction
       PARENT_SOUTH, //!< parent is in south direction
       PARENT_EAST,  //!< parent is in east direction
       PARENT_WEST   //!< parent is in west direction
}; 

/** A position on a Field */
struct Pos 
{
  Pos(short arg_x, short arg_y) : x(arg_x), y(arg_y) {}
  Pos() {}
 
  short x;
  short y;
};

inline float PosDistance(const Pos& a, const Pos& b)
{
  return sqrt((b.x - a.x) * (b.x - a.x)
              + (b.y - a.y) * (b.y - a.y));
}

inline float PosMDistance(const Pos& a, const Pos& b)
{
  return (b.x - a.x) * (b.x - a.x)
    + (b.y - a.y) * (b.y - a.y);
}

#endif

/* EOF */
