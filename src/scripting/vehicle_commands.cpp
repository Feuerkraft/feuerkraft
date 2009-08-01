//  $Id: vehicle_commands.cpp,v 1.2 2003/06/07 18:57:43 grumbel Exp $
//
//  Pingus - A free Lemmings clone
//  Copyright (C) 2002 Ingo Ruhnke <grumbel@gmx.de>
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//  
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//  
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include "../vehicles/helicopter.hpp"
#include "../vehicles/vehicle.hpp"
#include "../game_obj_manager.hpp"
#include "vehicle_commands.hpp"

int vehicle_find_nearest(float x, float y, float max_distance)
{
  Vehicle* nearest_vehicle = 0;
  float    nearest_vehicle_distance = 0;
  
  for (GameObjManager::iterator i = GameObjManager::current()->begin();
       i != GameObjManager::current()->end(); 
       ++i)
    {
      Vehicle* vehicle = dynamic_cast<Vehicle*>(*i);
      if (vehicle)
        {
          float distance = (vehicle->get_pos() - FloatVector2d(x, y)).get_length();
          if (distance <= max_distance)
            {
              if (nearest_vehicle)
                {
                  if (distance < nearest_vehicle_distance)
                    nearest_vehicle = vehicle;
                }
              else
                {
                  nearest_vehicle = vehicle;
                }
            }           
        }
    }
  if (nearest_vehicle)
    return nearest_vehicle->get_id();
  else
    return 0;
}

void
helicopter_start_or_land(int handle)
{
  GameObj* obj = GameObjManager::current()->get_object_by_id(handle);
  if (obj)
    {
      Helicopter* heli = dynamic_cast<Helicopter*>(obj);
      if (heli)
        heli->land_or_start();
    }
}

/* EOF */
