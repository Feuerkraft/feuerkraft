//  $Id: vehicle_view.cpp,v 1.11 2003/06/06 14:25:47 grumbel Exp $
//
//  Feuerkraft - A Tank Battle Game
//  Copyright (C) 2000 Ingo Ruhnke <grumbel@gmx.de>
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

#include <math.h>
#include "vehicle_view.hpp"

VehicleViewUpdater::VehicleViewUpdater (Unit* arg_unit)
  : unit(arg_unit)
{
  pos = unit->get_pos();
  speed = 0.1f;
  zoom_follower = 1.0f;
}

VehicleViewUpdater::~VehicleViewUpdater ()
{
}

void 
VehicleViewUpdater::update (float delta, ViewState& state)
{
  delta *= 50.0f;
  FloatVector2d target = unit->get_pos ();

#if 0  // FIXME:
  float zoom = (-fabs(unit->get_velocity ()/10.0f) + 1.0) * 1.5f;

  if (zoom_follower > zoom) zoom_follower -= 0.01 * delta;
  if (zoom_follower < zoom) zoom_follower += 0.01 * delta;

  state.zoom = zoom_follower;
#endif 

  if ((pos - target).get_length() > 1.0f)
    {
      FloatVector2d direction = (target - pos);
      pos += direction * speed;
   }
  
  state.x_offset = int(pos.x);
  state.y_offset = int(pos.y);

  float my_rotation = -(unit->get_orientation()/3.1415927*180.0) + 90;

  if (state.rotation > my_rotation) 
    state.rotation -= 2 * delta;
  
  if (state.rotation < my_rotation) 
    state.rotation += 2 * delta;
}

void
VehicleViewUpdater::set_unit(Unit* arg_unit)
{
  unit = arg_unit;
}

/* EOF */
