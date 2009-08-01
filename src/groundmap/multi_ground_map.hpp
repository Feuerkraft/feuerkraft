//  $Id: multi_ground_map.hpp,v 1.4 2003/06/03 14:11:22 grumbel Exp $
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

#ifndef MULTIGROUNDMAP_HXX
#define MULTIGROUNDMAP_HXX

#include <vector>
#include "multi_ground_map_data.hpp"
#include "ground_map.hpp"

class MultiGroundMap : public GroundMap,
		       public MultiGroundMapData
{
private:
  std::vector<GroundMap*> maps;

public:
  MultiGroundMap (const MultiGroundMapData& data);
  ~MultiGroundMap ();

  /** Return the type of ground, x and y are in world coordinates */
  GroundType get_groundtype (float x, float y);
  
  void draw(View& view);
  void draw_levelmap (LevelMap& levelmap);

  void add (GroundMap* groundmap);
};

#endif

/* EOF */
