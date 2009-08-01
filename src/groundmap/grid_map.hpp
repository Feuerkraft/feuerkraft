//  $Id: grid_map.hpp,v 1.7 2003/06/22 19:22:57 grumbel Exp $
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

#ifndef GRIDMAP_HXX
#define GRIDMAP_HXX

#include <vector>
#include <map>
#include <ClanLib/Display/surface.h>

#include "../view.hpp"
#include "ground_map.hpp"
#include "grid_tile_data.hpp"
#include "grid_map_data.hpp"
#include "grid_tile_generator.hpp"

class GridTile;

/**
   The GridMap works by having a grid of ground properties and
   generating a tilemap of that data. The ground properties define
   how a vehicle behaves on the ground, while the generated tiles are
   really just there to make it look good.
*/
class GridMap : public GroundMap,
		public GridMapData
{
private:
  /** width of the map in tiles */
  int width;

  /** height of the map in tiles */
  int height;
  
  /** This is the map, all tiles in this vector are just pointers to
      the tiles in 'tiles' */
  std::vector<GridTile*> gridmap;

  /** All real tiles are stored in this map, delete them here */
  GridTileGenerator tiles;

  /** A surface where each pixel-color represents a tile, used in the
      draw_levelmap() function */ 
  CL_Surface surface;

public:
  GridMap (const GridMapData& data);
  virtual ~GridMap ();

  /** Return the type of the ground at the world coordinates \a x and
      \a y */
  GroundType get_groundtype (float x, float y);

  void draw (View& view);
  void draw_levelmap (LevelMap& levelmap);
  void update (float);
};

#endif

/* EOF */
