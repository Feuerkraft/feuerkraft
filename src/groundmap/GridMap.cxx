//  $Id: GridMap.cxx,v 1.3 2002/03/25 19:30:56 grumbel Exp $
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

#include "GridTile.hxx"
#include "GridMap.hxx"

GridMap::GridMap (const GridMapData& data)
  : GridMapData (data)
{
  std::vector<GridTileData> tile_data;
  
  width  = grid_width  - 1;
  height = grid_height - 1;

  tile_data.resize (width * height);

  /* FIXME: Should be layed out into an .scm file */
  tiles[GridTileData (GT_SAND, GT_SAND, GT_SAND, GT_SAND)] 
    = new GridTile ("tiles/sand1");

  tiles[GridTileData (GT_FLATWATER, GT_FLATWATER, GT_FLATWATER, GT_FLATWATER)]
    = new GridTile ("tiles/water1");

  tiles[GridTileData (GT_DEEPWATER, GT_DEEPWATER, GT_DEEPWATER, GT_DEEPWATER)]
    = new GridTile ("tiles/deepwater1");

  tiles[GridTileData (GT_GRASS, GT_GRASS, GT_GRASS, GT_GRASS)] 
    = new GridTile ("tiles/grass1");

  tiles[GridTileData (GT_GRASS, GT_GRASS, GT_SAND, GT_SAND)] 
    = new GridTile ("tiles/sandgrass1");

  tiles[GridTileData (GT_GRASS, GT_SAND, GT_SAND, GT_GRASS)] 
    = new GridTile ("tiles/sandgrass2");

  tiles[GridTileData (GT_GRASS, GT_GRASS, GT_SAND, GT_GRASS)] 
    = new GridTile ("tiles/sandgrass3");

  tiles[GridTileData (GT_GRASS, GT_GRASS, GT_GRASS, GT_SAND)] 
    = new GridTile ("tiles/sandgrass4");

  tiles[GridTileData (GT_SAND, GT_GRASS, GT_GRASS, GT_GRASS)] 
    = new GridTile ("tiles/sandgrass5");

  tiles[GridTileData (GT_GRASS, GT_SAND, GT_GRASS, GT_GRASS)] 
    = new GridTile ("tiles/sandgrass6");

  tiles[GridTileData (GT_SAND, GT_SAND, GT_GRASS, GT_GRASS)] 
    = new GridTile ("tiles/sandgrass7");

  tiles[GridTileData (GT_SAND, GT_SAND, GT_GRASS, GT_SAND)] 
    = new GridTile ("tiles/sandgrass8");

  tiles[GridTileData (GT_SAND, GT_GRASS, GT_SAND, GT_SAND)] 
    = new GridTile ("tiles/sandgrass9");

  tiles[GridTileData (GT_SAND, GT_GRASS, GT_GRASS, GT_SAND)] 
    = new GridTile ("tiles/sandgrass10");

  tiles[GridTileData (GT_GRASS, GT_SAND, GT_SAND, GT_SAND)] 
    = new GridTile ("tiles/sandgrass11");


  tiles[GridTileData (GT_FLATWATER, GT_DEEPWATER, GT_DEEPWATER, GT_DEEPWATER)] 
    = new GridTile ("tiles/fddd");

  tiles[GridTileData (GT_FLATWATER, GT_DEEPWATER, GT_FLATWATER, GT_DEEPWATER)] 
    = new GridTile ("tiles/fdfd");

  tiles[GridTileData (GT_FLATWATER, GT_FLATWATER, GT_DEEPWATER, GT_DEEPWATER)] 
    = new GridTile ("tiles/ffdd");

  tiles[GridTileData (GT_FLATWATER, GT_FLATWATER, GT_FLATWATER, GT_DEEPWATER)] 
    = new GridTile ("tiles/fffd");

  tiles[GridTileData (GT_DEEPWATER, GT_FLATWATER, GT_FLATWATER, GT_DEEPWATER)] 
    = new GridTile ("tiles/dffd");

  tiles[GridTileData (GT_FLATWATER, GT_DEEPWATER, GT_DEEPWATER, GT_FLATWATER)] 
    = new GridTile ("tiles/fddf");

  tiles[GridTileData (GT_DEEPWATER, GT_FLATWATER, GT_FLATWATER, GT_FLATWATER)] 
    = new GridTile ("tiles/dfff");

  tiles[GridTileData (GT_FLATWATER, GT_DEEPWATER, GT_FLATWATER, GT_FLATWATER)] 
    = new GridTile ("tiles/fdff");

  tiles[GridTileData (GT_DEEPWATER, GT_DEEPWATER, GT_DEEPWATER, GT_FLATWATER)] 
    = new GridTile ("tiles/dddf");

  tiles[GridTileData (GT_FLATWATER,  GT_FLATWATER, GT_DEEPWATER, GT_FLATWATER)] 
    = new GridTile ("tiles/ffdf");

  tiles[GridTileData (GT_DEEPWATER, GT_FLATWATER, GT_DEEPWATER, GT_DEEPWATER)] 
    = new GridTile ("tiles/dfdd");


  tiles[GridTileData (GT_SAND, GT_FLATWATER, GT_FLATWATER, GT_SAND)] 
    = new GridTile ("tiles/sffs");
  tiles[GridTileData (GT_SAND, GT_SAND, GT_FLATWATER, GT_FLATWATER)] 
    = new GridTile ("tiles/ssff");
  tiles[GridTileData (GT_FLATWATER, GT_FLATWATER, GT_SAND, GT_SAND)] 
    = new GridTile ("tiles/ffss");
  tiles[GridTileData (GT_SAND, GT_SAND,  GT_FLATWATER,  GT_SAND)] 
    = new GridTile ("tiles/ssfs");
  tiles[GridTileData (GT_SAND, GT_SAND, GT_SAND, GT_FLATWATER)] 
    = new GridTile ("tiles/sssf");
  tiles[GridTileData (GT_FLATWATER, GT_SAND, GT_SAND, GT_SAND)] 
    = new GridTile ("tiles/fsss");
  tiles[GridTileData (GT_SAND, GT_FLATWATER, GT_SAND, GT_SAND)] 
    = new GridTile ("tiles/sfss");
  tiles[GridTileData (GT_FLATWATER, GT_SAND, GT_SAND, GT_SAND)] 
    = new GridTile ("tiles/fsss");
  tiles[GridTileData (GT_FLATWATER, GT_SAND, GT_FLATWATER, GT_FLATWATER)] 
    = new GridTile ("tiles/fsff");
  tiles[GridTileData (GT_SAND, GT_FLATWATER, GT_FLATWATER, GT_FLATWATER)] 
    = new GridTile ("tiles/sfff");
  tiles[GridTileData (GT_FLATWATER, GT_FLATWATER, GT_FLATWATER, GT_SAND)] 
    = new GridTile ("tiles/fffs");
  tiles[GridTileData (GT_FLATWATER, GT_SAND, GT_SAND, GT_FLATWATER)] 
    = new GridTile ("tiles/fssf");
  tiles[GridTileData (GT_FLATWATER, GT_SAND, GT_FLATWATER, GT_SAND)] 
    = new GridTile ("tiles/fsfs");
  tiles[GridTileData (GT_FLATWATER,GT_FLATWATER,GT_SAND, GT_FLATWATER)] 
    = new GridTile ("tiles/ffsf");
  tiles[GridTileData (GT_SAND, GT_FLATWATER,GT_SAND, GT_FLATWATER)] 
    = new GridTile ("tiles/sfsf");

  tiles[GridTileData (GT_SAND, GT_SAND, GT_SAND, GT_GRASS)] 
    = new GridTile ("tiles/sssg");

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
      gridmap[i] = tiles[tile_data[i]];
    }
}

GridMap::~GridMap ()
{
  
}

void
GridMap::draw (View* view)
{
  //std::cout << "Drawing" << std::endl;

  /* FIXME: This code should be shared with TileMap */
  int tile_x_offset = -(view->get_x_offset () / 40);
  int tile_y_offset = -(view->get_y_offset () / 40);
  int tile_width    = tile_x_offset + (view->get_width () / 40) + 1;
  int tile_height   = tile_y_offset + (view->get_height () / 40) + 1; 
  // FIXME: one tile more to avoid artefacts, hack, hack hack...
  
  for (int y = tile_y_offset; y < tile_height; ++y)
    for (int x = tile_x_offset; x < tile_width; ++x)
      {
	// FIXME: Hard coded gridmap size is ugly
	if (y < height && y >= 0 && x < width && x >= 0) // Could be optimized away
	  {
	    if (gridmap [(width * y) + x]) // Tile is not empty
	      {
		gridmap [(width * y) + x]->draw (view , 
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
