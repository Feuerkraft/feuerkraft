//  $Id: grid_map.hxx,v 1.3 2003/05/03 16:21:35 grumbel Exp $
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
#include <ClanLib/Display/surface.h>

#include "view.hxx"
#include "ground_map.hxx"
#include "grid_tile_data.hxx"
#include "grid_map_data.hxx"
#include "grid_tile_generator.hxx"

class GridTile;

class GridMap : public GroundMap,
		public GridMapData
{
private:
  int width;
  int height;
  
  /** This is the map, all tiles in this vector are just pointers to
      the tiles in 'tiles' */
  std::vector<GridTile*> gridmap;

  /** All real tiles are stored in this map, delete them here */
  GridTileGenerator tiles;

  CL_Surface surface;

public:
  GridMap (const GridMapData& data);
  virtual ~GridMap ();

  GroundType get_groundtype (float x, float y);
  void draw (View* view);
  void draw_levelmap (LevelMap* levelmap);
  void update (float);
};

#endif

/* EOF */
