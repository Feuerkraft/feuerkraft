//  $Id: BuildingMap.hxx,v 1.4 2002/03/17 16:42:24 grumbel Exp $
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

#ifndef BUILDINGMAP_HXX
#define BUILDINGMAP_HXX

#include <vector>
#include "BuildingMapData.hxx"
#include "../GameObj.hxx"

class View;
class Building;
class BuildingData;

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
  BuildingMap (boost::dummy_ptr<GameWorld> w, const BuildingMapData&);
  virtual ~BuildingMap () {}

  // Draw the object onto the screen
  virtual void draw (View* view);
  
  // Update the object once a game loop
  virtual void update (float);
};

#endif

/* EOF */
