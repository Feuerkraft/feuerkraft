//  $Id: building_map.cpp,v 1.9 2003/06/22 21:51:21 grumbel Exp $
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

#include <iostream>
#include "../view.hpp"
#include "building_map.hpp"
#include "building.hpp"

#include "tower.hpp"
#include "fuelstation.hpp"
#include "ammotent.hpp"
#include "headquarter.hpp"
#include "wall.hpp"
#include "wall_door.hpp"

BuildingMap::BuildingMap(const BuildingMapData& data) :
  BuildingMapData (data),
  buildings(),
  building_map()

{
  for (std::vector<BuildingData>::iterator i = buildings_data.begin ();
       i != buildings_data.end ();
       ++i)
    {
      if (i->first == "tower")
	{
	  buildings.push_back(new Tower(i->second));
	}
      else if ("ammotent" == i->first)
	{
	  buildings.push_back(new Ammotent(i->second));
	}
      else if ("wall" == i->first)
	{
	  buildings.push_back(new Wall(i->second));
	}
      else if ("fuelstation" == i->first)
	{
	  //std::cout << "BuildingMapData: creating ammotent" << std::endl;
	  buildings.push_back(new Fuelstation(i->second));
	}
      else if ("headquarter" == i->first)
	{
	  //std::cout << "BuildingMapData: creating headquarter" << std::endl;
	  buildings.push_back(new Headquarter(i->second));
	}
      else if ("walldoor" == i->first)
	{
	  buildings.push_back(new WallDoor(i->second));
	}
      else
	{
	  std::cout << "BuildingMapData: Error: " << i->first << std::flush;
	}
    }

  building_map.resize(width * height);
  
  // Clear all pointers in the building map
  for (std::vector<Building*>::iterator i = building_map.begin();
       i != building_map.end();
       ++i)
    {
      *i = NULL;
    }

  // 'Draw' the buildings onto the building_map
  for (std::vector<Building*>::iterator i = buildings.begin();
       i != buildings.end ();
       ++i)
    {
      Building* building = *i;
      
      for (int x = building->get_x_pos();
	   x < building->get_x_pos() + building->get_map_width();
	   ++x)
	{
	  for (int y = building->get_y_pos(); 
	       y < building->get_y_pos() + building->get_map_height();
	       ++y)
	    {
	      if (x >= 0 && x < width && y >= 0 && y < height)
		building_map[(y * width) + x] = building;
	      else
		std::cout << "BuildingMap: Error: building position out of range: " << x << ", " << y << std::endl;
	    }
	}
    }
}

// Draw the object onto the screen
void
BuildingMap::draw (View& view)
{
  for (std::vector<Building*>::iterator i = buildings.begin ();
       i != buildings.end ();
       ++i)
    {
      (*i)->draw (view);
    }
}

void
BuildingMap::draw_energie (View& view)
{
  for (std::vector<Building*>::iterator i = buildings.begin ();
       i != buildings.end ();
       ++i)
    {
      (*i)->draw_energie (view);
    }  
}

void
BuildingMap::draw_radar (Radar& radar)
{
  for (std::vector<Building*>::iterator i = buildings.begin ();
       i != buildings.end ();
       ++i)
    {
      (*i)->draw_radar (radar);
    }  
}
  
// Update the object once a game loop
void
BuildingMap::update (float delta)
{
  for (std::vector<Building*>::iterator i = buildings.begin ();
       i != buildings.end ();
       ++i)
    {
      (*i)->update (delta);
    }
}

Building*
BuildingMap::get_building (const FloatVector2d& pos)
{
  int x = int(pos.x)/40;
  int y = int(pos.y)/40;

  if (pos.x < 0)
    x -= 1;

  if (pos.y < 0)
    y -= 1;

  if (x >= 0 && x < width && y >=0 && y < height)
    {
      Building* b = building_map[(y * width) + x];
      if (b && b->alive () && b->is_active ())
	return b;
      else
	return NULL;
    }
  else
    return NULL;
}

GameObjData*
BuildingMap::get_data ()
{
  // FIXME: No Sync
  return this;
}

void
BuildingMap::add_building(Building* building, int x_pos, int y_pos)
{
  //std::cout << "Adding building " << building << " at " << x_pos << ", " << y_pos << std::endl;

  for (int x = x_pos; x < x_pos + building->get_map_width(); ++x)
    {
      for (int y = y_pos; y < y_pos + building->get_map_height(); ++y)
        {
          if (x >= 0 && x < width && y >= 0 && y < height)
            building_map[(y * width) + x] = building;
          else
            std::cout << "BuildingMap: Error: building position out of range: " << x << ", " << y << std::endl;
        }
    }

  buildings.push_back(building);
}

/* EOF */
