//  $Id: building_type_manager.hxx,v 1.1 2003/05/08 23:02:10 grumbel Exp $
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

#ifndef HEADER_BUILDING_TYPE_MANAGER_HXX
#define HEADER_BUILDING_TYPE_MANAGER_HXX

#include <vector>
#include "../alist.hxx"
#include "custom_building.hxx"

class Building;

struct BuildingFactory {
  int id;
  
  virtual Building* create(const AList& lst) =0;
};

struct CustomBuildingFactory 
  : public BuildingFactory
{
  AList prefs;
  CustomBuildingFactory(const AList& arg_prefs)
    : prefs(arg_prefs)
  {}

  virtual ~CustomBuildingFactory() {}

  Building* create(const AList& lst) {
    return new CustomBuilding(prefs, lst);
  }
};

template<class C>
struct GenericBuildingFactory 
  : public BuildingFactory 
{
  Building* create(const AList& lst) {
    return new C(lst);
  }
};

/** */
class BuildingTypeManager
{
private:
  static BuildingTypeManager* current_;
public:
  static BuildingTypeManager* current() { return current_; }
private:
  int next_id;

  typedef std::vector<BuildingFactory*>  Factories;
  Factories factories;
public:
  BuildingTypeManager();

  /** Register a building factory
      @return handle for this type of building */
  int register_factory(BuildingFactory* factory);

  Building* create_building(int type_id, const AList& params);
  
private:
  BuildingTypeManager (const BuildingTypeManager&);
  BuildingTypeManager& operator= (const BuildingTypeManager&);
};

#endif

/* EOF */
