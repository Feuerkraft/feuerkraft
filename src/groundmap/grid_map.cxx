//  $Id: grid_map.cxx,v 1.8 2003/06/08 15:31:27 grumbel Exp $
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

#include "grid_tile.hxx"
#include "grid_map.hxx"

GridMap::GridMap (const GridMapData& data)
  : GridMapData (data),
    tiles ("data/tiles.scm"),
    surface (provider)
{
  std::vector<GridTileData> tile_data;
  
  width  = grid_width  - 1;
  height = grid_height - 1;

  tile_data.resize (width * height);

  /* Generated a temporary tile_data */
  for (int y = 0; y < height; ++y)
    {
      for (int x = 0; x < width; ++x)
	{
	  tile_data[x + (y * width)] = GridTileData (grid_data[(x + 0) + ((y + 0) * grid_width)],
						     grid_data[(x + 1) + ((y + 0) * grid_width)],
						     grid_data[(x + 1) + ((y + 1) * grid_width)],
						     grid_data[(x + 0) + ((y + 1) * grid_width)]);
	}
    }

  gridmap.resize (tile_data.size ());
  for (unsigned int i = 0; i != tile_data.size (); ++i)
    {
      gridmap[i] = tiles.create(tile_data[i]);
    }
}

GridMap::~GridMap ()
{
  
}

void
GridMap::draw (View& view)
{
  //std::cout << "Drawing" << std::endl;

  /* FIXME: This code should be shared with TileMap */
  int tile_x_offset = int(-(view.get_x_offset ()) / 40);
  int tile_y_offset = int(-(view.get_y_offset ()) / 40);
  int tile_width    = tile_x_offset + (view.get_width()  / 40) + 2;
  int tile_height   = tile_y_offset + (view.get_height() / 40) + 2; 
  // FIXME: one tile more to avoid artefacts, hack, hack hack...
  
  for (int y = tile_y_offset; y < tile_height; ++y)
    for (int x = tile_x_offset; x < tile_width; ++x)
      {
	// FIXME: Hard coded gridmap size is ugly
	if (y < height && y >= 0 && x < width && x >= 0) // Could be optimized away
	  {
	    if (gridmap [(width * y) + x]) // Tile is not empty
	      {
		gridmap [(width * y) + x]->draw (view, 
						 int(x * 40) + 20, // FIXME: Map offset needs to be
						 int(y * 40) + 20); // FIXME: configurable;
	      }
	    else
	      {
		//std::cout << "Empty tile at: "<< x << "x" << y << std::endl;
	      }
	  }
      }
}

void
GridMap::update (float)
{
  
}

void
GridMap::draw_levelmap (LevelMap& levelmap)
{
  surface.set_alpha(0.9f);
  surface.draw (0, 0);
  surface.set_alpha(1.0f);
}

GroundType
GridMap::get_groundtype (float x, float y)
{
  // FIXME: This doesn't look right
  int ix = int((x + 20) / 40);
  int iy = int((y + 20) / 40);

  if (ix >= 0 && ix < grid_width && iy >= 0 && iy < grid_height)
    return grid_data[ix + (iy * grid_width)];
  else
    return GT_EMPTY;
}

/* EOF */
