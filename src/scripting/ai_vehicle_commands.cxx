//  $Id: ai_vehicle_commands.cxx,v 1.5 2003/06/03 14:11:22 grumbel Exp $
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
#include "../game_obj_manager.hxx"
#include "../ai_vehicle.hxx"
#include "ai_vehicle_commands.hxx"

static AIVehicle*
get_AIVehicle(int object_id)
{
  AIVehicle* vehicle = dynamic_cast<AIVehicle*>(GameObjManager::current()->get_object_by_id(object_id));
  if (vehicle)
    {
      return vehicle;
    }
  else
    {
      std::cout  << "AIVehicle: no object given by id: " << object_id << std::endl;
      return 0;
    }
}
 

int
ai_vehicle_create(int x, int y)
{
  AIVehicle* vehicle = new AIVehicle(FloatVector2d(x,y));

  return GameObjManager::current()->add_object(vehicle);
}

void
ai_vehicle_wait(int object_id, float seconds)
{
  AIVehicle* vehicle = get_AIVehicle(object_id);

  if (vehicle)
    vehicle->wait(seconds);
}

void
ai_vehicle_drive_to(int object_id, int x, int y)
{
  AIVehicle* vehicle = get_AIVehicle(object_id);

  if (vehicle)
    vehicle->drive_to(FloatVector2d(x, y));
}

void
ai_vehicle_clear_orders(int object_id)
{
  AIVehicle* vehicle = get_AIVehicle(object_id);

  if (vehicle)
    vehicle->clear_orders();
}

/* EOF */
