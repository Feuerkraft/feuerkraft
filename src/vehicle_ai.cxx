//  $Id: vehicle_ai.cxx,v 1.1 2003/06/18 00:27:09 grumbel Exp $
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

#include "math.hxx"
#include "vehicle.hxx"
#include "vehicle_ai.hxx"

VehicleAI::VehicleAI(Vehicle* arg_vehicle)
  : vehicle(arg_vehicle)
{
}

VehicleRoboAI::VehicleRoboAI(Vehicle* vehicle)
  : VehicleAI(vehicle)
{
  ai_count = 0;
}

void
VehicleRoboAI::update(float delta)
{
  ai_count += delta;
  
  if (ai_count > 2)
    {
      ai_count = 0;
      
      switch (rand() % 5)
        {
        case 0:
        case 1:
        case 2:
          controller.set_axis_state(ACCELERATE_AXIS, 1.0f);
          break;
        case 3:
          controller.set_axis_state(ACCELERATE_AXIS, -1.0f);
          break;
        case 4:
          controller.set_axis_state(ACCELERATE_AXIS, 0.0f);
          break;
        }

      controller.set_axis_state(ORIENTATION_AXIS, Math::frand() * 2.0f - 1.0f);
    }
  
  vehicle->update_controlls(controller);
}

VehiclePathAI::VehiclePathAI(Vehicle* vehicle)
  : VehicleAI(vehicle),
    driving(false),
    length(0.0f),
    line_segments(vehicle->get_pos().x, 
                  vehicle->get_pos().y,
                  vehicle->get_orientation())
{
}

void
VehiclePathAI::update(float delta)
{
  if (driving)
    {
      length += 100.0f * delta;

      vehicle->set_position(line_segments.get_pos(length));
      vehicle->set_orientation(line_segments.get_orientation(length));

      if (line_segments.get_length() < length)
        driving = false;
    }
}

void
VehiclePathAI::drive_to(const FloatVector2d& pos)
{
  driving = true;
  line_segments.add_controll_point(pos.x, pos.y, 50.0f);  
}

/* EOF */
