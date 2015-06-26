// Feuerkraft - A Tank Battle Game
// Copyright (C) 2002 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include "../game_world.hpp"
#include "building_map.hpp"
#include "building.hpp"
#include "building_manager.hpp"

BuildingManager* BuildingManager::current_ = 0;
int BuildingManager::next_id = 1;

BuildingManager::BuildingManager() :
  buildings()
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
