//  $Id: building_map.hpp,v 1.9 2003/06/22 19:22:56 grumbel Exp $
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

#ifndef BUILDINGMAP_HXX
#define BUILDINGMAP_HXX

#include <vector>
#include "building_map_data.hpp"
#include "../game_obj.hpp"

class FloatVector2d;
class View;
class Building;
class Radar;

typedef Building* BuildingPtr;

class BuildingMap : public BuildingMapData,
		    public GameObj
{
private:
  /** A list with all the buildings in this map, the pointers here need to be deleted! */
  std::vector<Building*> buildings;

  /** This is a 'TileMap' with points to all buildings. Pointers in
      this list must not be deleted, they are only references to
      'buildings' */
  std::vector<Building*> building_map;

public:
  BuildingMap (const BuildingMapData&);
  virtual ~BuildingMap () {}

  int get_width () { return width; }
  int get_height () { return height; }

  // Draw the object onto the screen
  virtual void draw (View& view);
  virtual void draw_energie (View& view);
  virtual void draw_radar (Radar& radar);
  
  // Update the object once a game loop
  virtual void update (float);

  void add_building(Building* building, int x, int y);

  BuildingPtr get_building (const FloatVector2d& pos);
  
  /** FIXME: Not the cleanest API solution */
  std::vector<Building*>& get_buildings ();

  GameObjData* get_data ();
};

#endif

/* EOF */
