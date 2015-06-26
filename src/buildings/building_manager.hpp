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

#ifndef HEADER_FEUERKRAFT_BUILDING_MANAGER_HXX
#define HEADER_FEUERKRAFT_BUILDING_MANAGER_HXX

#include <vector>

class Building;

/** */
class BuildingManager
{
private:
  static BuildingManager* current_;
  static int next_id;
public:
  static BuildingManager* current() { return current_; }

private:
  typedef std::vector<Building*> Buildings;
  Buildings buildings;

public:
  BuildingManager();
  ~BuildingManager();

  Building* get_building_by_id(int handle);
  void add_building(Building* building, int x, int y);

private:
  BuildingManager (const BuildingManager&);
  BuildingManager& operator= (const BuildingManager&);
};

#endif

/* EOF */
