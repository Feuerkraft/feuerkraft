//  $Id: tile_map_data.hxx,v 1.1 2003/04/19 22:39:07 grumbel Exp $
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

#ifndef TILEMAPDATA_HXX
#define TILEMAPDATA_HXX

#include <guile/gh.h>
#include <vector>

#include "GroundMapData.hxx"

class TileData;
class TileMap;

/** TileMapData holds all data that is necesarry for creating a TileMap
 */
class TileMapData : public GroundMapData
{
public:
  int width;
  int height;

  /** Data for creating Tile's */
  std::vector<TileData*> tiles_data;

  /** Data for the tilemap, each 'int' here, refers to a position in
      tiles_data */
  std::vector<int> tilemap_data;

public:
  /** Create a TileMapData out of an SCM description, the structure is
      like this:
      
      (tilemap (width 100)
               (height 100)
               (tiles (spritetile ...)
                      (someothertiletype ...)
                       ...)
               (map 1 2 3 4 5 2 3 11 2 3 ...))
   */
  TileMapData (SCM desc);
  virtual ~TileMapData ();

private:
  void parse_from_file (SCM desc);
  void parse_tiles (SCM desc);
  void parse_map (SCM desc);

public:
  GroundMap* create ();
};

#endif

/* EOF */
