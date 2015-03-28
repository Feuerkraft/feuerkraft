//  $Id: tile_map_data.hpp,v 1.3 2003/06/03 14:11:22 grumbel Exp $
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

#ifndef TILEMAPDATA_HXX
#define TILEMAPDATA_HXX

#include <guile/gh.h>
#include <vector>

#include "ground_map_data.hpp"

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
