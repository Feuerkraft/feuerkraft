//  $Id: building_type_manager.hxx,v 1.2 2003/05/10 22:41:28 grumbel Exp $
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
  /** The id by which the factory can be refered to */
  int id;

  /** A symbolic name for the factory, which is another way to refer
      to the factory. It is used for serialisations for better
      portability. */
  std::string name;

  BuildingFactory() {}
  virtual ~BuildingFactory() {}

  virtual Building* create(const AList& lst) =0;
};

struct CustomBuildingFactory 
  : public BuildingFactory
{
  AList prefs;
  CustomBuildingFactory(const std::string& arg_name, const AList& arg_prefs)
    : prefs(arg_prefs)
  {
    name = arg_name;
  }

  virtual ~CustomBuildingFactory() {}

  Building* create(const AList& lst) {
    return new CustomBuilding(prefs, lst);
  }
};

template<class C>
struct GenericBuildingFactory 
  : public BuildingFactory 
{
  GenericBuildingFactory(const std::string& arg_name) 
  {
    name = arg_name;
  }
  
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

  int name_to_id(const std::string& name);
  std::string id_to_name(int id);

  Building* create_building(int type_id, const AList& params);
  
private:
  BuildingTypeManager (const BuildingTypeManager&);
  BuildingTypeManager& operator= (const BuildingTypeManager&);
};

#endif

/* EOF */
