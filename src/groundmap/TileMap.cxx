//  $Id: TileMap.cxx,v 1.13 2002/03/24 23:26:41 grumbel Exp $
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

#include "Tile.hxx"
#include "TileData.hxx"
#include "TileMap.hxx"

TileMap::TileMap (const TileMapData& data)
  : TileMapData (data)
{
  // Create the tiles from tiles_data
  for (std::vector<TileData*>::iterator it = tiles_data.begin ();
       it != tiles_data.end ();
       ++it)
    {
      //std::cout << "Tiles: " << *it << std::endl;
      if (*it)
	tiles.push_back ((*it)->create_Tile ());
      else
	tiles.push_back (NULL);
    }

  // Create the tilemap out of tiles_data and tiles
  tilemap.resize (tilemap_data.size ());
  for (unsigned int i = 0; i < tilemap.size (); ++i)
    {
      if (tilemap_data[i] >= 0 && tilemap_data[i] < int(tiles.size()))
	{
	  tilemap[i] = tiles[tilemap_data[i]];
	  //std::cout << "Tile: " << tilemap_data[i] << " " << tiles[tilemap_data[i]] << std::endl;
	}
      else
	{
	  //std::cout << "Tile" << tiles.size() << ": " << tilemap_data[i] << std::endl;
	}
    }
  
  //std::cout << "Tilemap: " << width << "x" << height << std::endl;

}

TileMap::~TileMap ()
{
  for (std::vector<Tile*>::iterator i = tiles.begin (); i != tiles.end (); ++i)
    delete *i;
}

GroundType
TileMap::get_groundtype (float x, float y)
{
  return GT_FLATWATER;
}

void
TileMap::draw (View* view)
{
  //std::cout << "Offset: " << view->get_x_offset () << std::endl;

  int tile_x_offset = -(view->get_x_offset () / 40);
  int tile_y_offset = -(view->get_y_offset () / 40);
  int tile_width    = tile_x_offset + (view->get_width () / 40) + 1;
  int tile_height   = tile_y_offset + (view->get_height () / 40) + 1; 
 // FIXME: one tile more to avoid artefacts, hack, hack hack...
  

  for (int y = tile_y_offset; y < tile_height; ++y)
    for (int x = tile_x_offset; x < tile_width; ++x)
    {
      // FIXME: Hard coded tilemap size is ugly
      if (y < height && y >= 0 && x < width && x >= 0) // Could be optimized away
	if (tilemap [(width * y) + x])
	  tilemap [(width * y) + x]->draw (view , 
					   int(x * 40),
					   int(y * 40));
    }
}

void
TileMap::update (float delta)
{
  //std::cout << "TileMap::update" << std::endl;
  for (std::vector<Tile*>::iterator i = tiles.begin (); i != tiles.end (); ++i)
    if (*i)
      (*i)->update (delta);
}

/* EOF */
