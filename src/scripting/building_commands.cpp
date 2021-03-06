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

#include <iostream>
#include <libguile.h>
#include "../guile.hpp"
#include "../game_world.hpp"
#include "../property.hpp"
#include "../property_set.hpp"
#include "../buildings/building.hpp"
#include "../buildings/custom_building.hpp"
#include "../buildings/building_type_manager.hpp"
#include "../buildings/building_manager.hpp"
#include "building_commands.hpp"

int
building_create(int type, int x, int y)
{
  Building* building;

  if (type == 1)
    {
      building = 0;
    }
  else
    {
      AList props;
      props.set_int("x-pos", x);
      props.set_int("y-pos", y);
      building = BuildingTypeManager::current()->create_building(type, props);
    }

  if (building)
    {
      BuildingManager::current()->add_building(building, x, y);
      return building->get_id();
    }
  else
    {
      std::cout << "BuildingCommands: Unhandled building type: " << type << std::endl;
      return 0;
    }
}

void
building_remove(int handle)
{
}

int
building_get_tile(int x, int y)
{
  return 0;
}

int
building_get(int x, int y)
{
  return 0;
}

int
building_create_type(const char* name, SCM lst)
{
  AList alist;

  while(!scm_is_true(scm_null_p(lst)))
    {
      SCM key   = scm_car(lst);

      if (scm_is_true(scm_null_p(scm_cdr(lst))))
        {
          std::cout << "Missing argument to keyword!" << std::endl;
        }

      SCM value = scm_cadr(lst);

      if (scm_is_true(scm_boolean_p(value)))
        {
          alist.set_bool(Guile::keyword2string(key), scm_to_bool(value));
        }
      else if (scm_is_true(scm_number_p(value)))
        {
          alist.set_int(Guile::keyword2string(key), scm_to_int(value));
        }
      else if (scm_is_true(scm_string_p(value)))
        {
          alist.set_string(Guile::keyword2string(key), Guile::scm2string(value));
        }
      else
        {
          std::cout << "BuildingCommands: unknown argumnent type" << std::endl;
        }

      lst = scm_cddr(lst);
    }

  return BuildingTypeManager::current()->register_factory(new CustomBuildingFactory(name, alist));
}

SCM
building_get_property(int handle, const char* name)
{
  Building* building = BuildingManager::current()->get_building_by_id(handle);
  if (!building)
    {
      std::cout << "building_get_property: unknown handle: " << handle << std::endl;
      return SCM_UNSPECIFIED;
    }
  else
    {
      PropertySet* properties = building->get_properties();
      if (!properties)
        {
          return SCM_UNSPECIFIED;
        }
      else
        {
          Property* property = properties->lookup(name);

          if (!property)
            {
              return SCM_UNSPECIFIED;
            }
          else
            {
              return Guile::property2scm(*property);
            }
        }
    }
}

void
building_set_property(int handle, const char* name, SCM value)
{
  Building* building = BuildingManager::current()->get_building_by_id(handle);
  if (!building)
    {
      std::cout << "building_set_property: unknown handle: " << handle << std::endl;
    }
  else
    {
      PropertySet* properties = building->get_properties();
      if (!properties)
        {
          std::cout << "building_set_property: object has no properties" << std::endl;
        }
      else
        {
          Guile::scm2property(*properties, name, value);
        }
    }
}

int
building_get_type_from_name(const char* name)
{
  return BuildingTypeManager::current()->name_to_id(name);
}

/* EOF */
