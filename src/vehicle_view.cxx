//  $Id: vehicle_view.cxx,v 1.8 2003/05/19 21:46:21 grumbel Exp $
//
//  Pingus - A free Lemmings clone
//  Copyright (C) 2000 Ingo Ruhnke <grumbel@gmx.de>
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

#include <math.h>
#include "vehicle_view.hxx"

VehicleViewUpdater::VehicleViewUpdater (VehiclePtr arg_vehicle)
  : vehicle (arg_vehicle)
{
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
  FloatVector2d target = vehicle->get_pos ();
 
  float zoom = (-fabs(vehicle->get_velocity ()/10.0f) + 1.0) * 1.5f;

  if (zoom_follower > zoom) zoom_follower -= 0.01 * delta;
  if (zoom_follower < zoom) zoom_follower += 0.01 * delta;

  state.zoom = zoom_follower;

  if ((pos - target).get_length() > 1.0f)
    {
      FloatVector2d direction = (target - pos);
      pos += direction * speed;
   }
  
  state.x_offset = int(pos.x);
  state.y_offset = int(pos.y);

  float my_rotation = -(vehicle->get_angle ()/3.1415927*180.0) + 90;

  if (state.rotation > my_rotation) 
    state.rotation -= 2 * delta;
  
  if (state.rotation < my_rotation) 
    state.rotation += 2 * delta;
}

void
VehicleViewUpdater::set_vehicle (VehiclePtr arg_vehicle)
{
  vehicle = arg_vehicle;
}

/* EOF */
