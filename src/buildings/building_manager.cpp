//  $Id: building_manager.cxx,v 1.3 2003/06/03 14:11:22 grumbel Exp $
//
//  Feuerkraft - A Tank Battle Game
//  Copyright (C) 2002 Ingo Ruhnke <grumbel@gmx.de>
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

#include "../game_world.hxx"
#include "building_map.hxx"
#include "building.hxx"
#include "building_manager.hxx"

BuildingManager* BuildingManager::current_ = 0;
int BuildingManager::next_id = 1;

BuildingManager::BuildingManager()
{
  current_ = this;
}

BuildingManager::~BuildingManager()
{
  
}

Building*
BuildingManager::get_building_by_id(int handle)
{
  for(Buildings::iterator i = buildings.begin(); i != buildings.end(); ++i)
    {
      if ((*i)->get_id() == handle)
        return *i;
    }
  return 0;
}

void
BuildingManager::add_building(Building* building, int x, int y)
{
  buildings.push_back(building);
  building->set_id(next_id);
  ++next_id;

  GameWorld::current()->get_buildingmap()->add_building(building, x, y);
}

/* EOF */
