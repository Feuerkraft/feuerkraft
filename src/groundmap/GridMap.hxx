//  $Id: GridMap.hxx,v 1.1 2002/03/25 09:57:11 grumbel Exp $
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

#ifndef GRIDMAP_HXX
#define GRIDMAP_HXX

#include <vector>
#include <map>
#include "GroundMap.hxx"
#include "GridTileData.hxx"
#include "GridMapData.hxx"

class GridTile;

class GridMap : public GroundMap,
		public GridMapData
{
private:
  /** This is the map, all tiles in this vector are just pointers to
      the tiles in 'tiles' */
  std::vector<GridTile*> gridmap;

  /** All real tiles are stored in this map, delete them here */
  std::map<GridTileData, GridTile*> tiles;

public:
  GridMap (const GridMapData& data);
  virtual ~GridMap ();

  GroundType get_groundtype (float x, float y);
  void draw (View* view);
  void update (float);
};

#endif

/* EOF */
