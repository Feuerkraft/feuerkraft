//  $Id: building_manager.hxx,v 1.1 2003/05/08 20:07:06 grumbel Exp $
// 
//  Pingus - A free Lemmings clone
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