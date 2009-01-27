//  $Id: grid_tile_data.hpp,v 1.4 2003/10/31 23:24:41 grumbel Exp $
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

#ifndef GRIDTILEDATA_HXX
#define GRIDTILEDATA_HXX

#include <iostream>
#include "ground_type.hpp"

class GridTile;

/** A GridTileData object consistf a logical description of a grid
    tile, which means the ground type of each edge will be described.
    Via the create() call a fitting Tile can be generated. */
class GridTileData
{
public:
  GroundType ul;
  GroundType ur;
  GroundType br;
  GroundType bl;

public:
  GridTileData ()
  {
    // FIXME: We could make this even more abstract and not use
    // groundtype directly, so that we could apply theming support
    // (night, day, winter)
    ul = ur = br = bl = GT_SAND;
  }

  GridTileData (GroundType arg_ul, GroundType arg_ur, GroundType arg_br, GroundType arg_bl)
    : ul (arg_ul), ur (arg_ur), br (arg_br), bl (arg_bl)
  {
  }

  GridTile* create ();

  bool operator==(const GridTileData& a);
};

bool operator<(const GridTileData& a, const GridTileData& b);
std::ostream& operator<<(std::ostream& s, const GridTileData& b);

#endif

/* EOF */
