//  $Id: building_commands.cxx,v 1.10 2003/06/03 14:11:22 grumbel Exp $
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
#include "../guile.hxx"
#include "../game_world.hxx"
#include "../property.hxx"
#include "../property_set.hxx"
#include "../buildings/building.hxx"
#include "../buildings/custom_building.hxx"
#include "../buildings/wall_data.hxx"
#include "../buildings/building_type_manager.hxx"
#include "../buildings/building_manager.hxx"
#include "building_commands.hxx"

int
building_create(int type, int x, int y)
{
  Building* building;

  if (type == 1)
    {
      WallData data;

      data.energie = 100;
      data.x_pos = x;
      data.y_pos = y;

      building = data.create();
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
  
  while(!gh_null_p(lst))
    {
      SCM key   = gh_car(lst);

      gh_display(key);
      gh_newline();

      if (gh_null_p(gh_cdr(lst)))
        {
          std::cout << "Missing argument to keyword!" << std::endl;
        }

      SCM value = gh_cadr(lst);

      gh_display(value);
      gh_newline();
      
      if (gh_boolean_p(value))
        {
          alist.set_bool(Guile::keyword2string(key), gh_scm2bool(value));
        }
      else if (gh_number_p(value))
        {
          alist.set_int(Guile::keyword2string(key), gh_scm2int(value));
        }
      else if (gh_string_p(value))
        {
          alist.set_string(Guile::keyword2string(key), Guile::scm2string(value));
        }
      else
        {
          std::cout << "BuildingCommands: unknown argumnent type" << std::endl;
        }

      lst = gh_cddr(lst);
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

/* EOF */
