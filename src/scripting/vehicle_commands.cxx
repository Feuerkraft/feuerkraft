//  $Id: vehicle_commands.cxx,v 1.1 2003/06/04 13:16:17 grumbel Exp $
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

#include "../vehicle.hxx"
#include "../game_obj_manager.hxx"
#include "vehicle_commands.hxx"

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

/* EOF */
