//  $Id: TileMap.cxx,v 1.3 2002/03/09 14:53:51 grumbel Exp $
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
  for (std::vector<TileData*>::iterator i = tiles_data.begin ();
       i != tiles_data.end ();
       ++i)
    {
      if (*i)
	tiles.push_back ((*i)->create_Tile ());
      else
	tiles.push_back (NULL);
    }
}

TileMap::~TileMap ()
{
  for (std::vector<Tile*>::iterator i = tiles.begin (); i != tiles.end (); ++i)
    delete *i;
}

GroundType
TileMap::get_groundtype (float x, float y)
{
  return GT_SAND;
}

void
TileMap::draw (View* view)
{
  //std::cout << "TileMap::draw" << std::endl;

  for (std::vector<Tile*>::size_type y = 0; y < height; ++y)
    for (std::vector<Tile*>::size_type x = 0; x < width; ++x)
    {
      if (tiles [(width * y) + x])
	tiles [(width * y) + x]->draw (x * 32, y * 32);
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
