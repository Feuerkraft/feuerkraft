//  $Id: building_commands.cxx,v 1.3 2003/05/08 23:02:10 grumbel Exp $
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

#include <iostream>
#include "../game_world.hxx"
#include "buildings/building.hxx"
#include "buildings/custom_building.hxx"
#include "buildings/wall_data.hxx"
#include "buildings/building_type_manager.hxx"
#include "buildings/building_manager.hxx"
#include "building_commands.hxx"

int  building_create(int type, int x, int y)
{
  Building* building;

  if (type == 1)
    {
      WallData data;

      data.energie = 100;
      data.x_pos = x;
      data.y_pos = y;

      building = data.create(GameWorld::current());
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

void building_remove(int handle)
{
}

int  building_get_tile(int x, int y)
{
  return 0;
}

int  building_get(int x, int y)
{
  return 0;
}

int building_create_type(SCM lst)
{
  return BuildingTypeManager::current()->register_factory(new CustomBuildingFactory(AList()));
}

/* EOF */
