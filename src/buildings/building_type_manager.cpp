//  $Id: building_type_manager.cxx,v 1.5 2003/06/23 09:56:39 grumbel Exp $
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

#include <iostream>

#include "wall_door.hxx"
#include "wall.hxx"
#include "tower.hxx"
#include "fuelstation.hxx"
#include "ammotent.hxx"

#include "building_type_manager.hxx"

BuildingTypeManager* BuildingTypeManager::current_ = 0;

BuildingTypeManager::BuildingTypeManager()
{
  next_id = 2;
  current_ = this;

  register_factory(new GenericBuildingFactory<Fuelstation>("fuelstation"));
  register_factory(new GenericBuildingFactory<Ammotent>("ammotent"));
  register_factory(new GenericBuildingFactory<Wall>("wall"));
  register_factory(new GenericBuildingFactory<WallDoor>("walldoor"));
  register_factory(new GenericBuildingFactory<Tower>("tower"));
}

int
BuildingTypeManager::register_factory(BuildingFactory* factory)
{
  factories.push_back(factory);
  factory->id = next_id;
  return next_id++;
}

Building*
BuildingTypeManager::create_building(int type_id, const AList& params)
{
  for (Factories::iterator i = factories.begin(); i != factories.end(); ++i)
    {
      if ((*i)->id == type_id)
        {
          return (*i)->create(params);
        }
    }

  // FIXME: throw something here
  std::cout << "BuildingTypeManager: Invalid type handle: " << type_id << std::endl;
  return 0;
}

int
BuildingTypeManager::name_to_id(const std::string& name)
{
 for (Factories::iterator i = factories.begin(); i != factories.end(); ++i)
    {
      if ((*i)->name == name)
        {
          return (*i)->id;
        }
    }
 // FIXME: throw something here
 return 0;
}

std::string
BuildingTypeManager::id_to_name(int id)
{
 for (Factories::iterator i = factories.begin(); i != factories.end(); ++i)
    {
      if ((*i)->id == id)
        {
          return (*i)->name;
        }
    }
 // FIXME: throw something here
 return "invalid-id";
}

/* EOF */
