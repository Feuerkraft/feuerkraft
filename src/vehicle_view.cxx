//  $Id: vehicle_view.cxx,v 1.5 2003/05/18 21:15:06 grumbel Exp $
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

VehicleView::VehicleView (VehiclePtr arg_vehicle, 
			  int x1, int y1, int x2, int y2, CL_GraphicContext* arg_gc) :
  View (x1, y1, x2, y2,
	int(-arg_vehicle->get_pos ().x), int(-arg_vehicle->get_pos ().y),
	arg_gc),
  vehicle (arg_vehicle)
{
  speed = 0.1f;
  zoom_follower = 1.0f;
}

VehicleView::~VehicleView ()
{
}

void 
VehicleView::update (float delta)
{
  delta *= 50.0f;
  FloatVector2d target = vehicle->get_pos ();
 
  float zoom = (-fabs(vehicle->get_velocity ()/10.0f) + 1.0) * 1.5f;

  if (zoom_follower > zoom) zoom_follower -= 0.01 * delta;
  if (zoom_follower < zoom) zoom_follower += 0.01 * delta;

  set_zoom(zoom_follower);

  if ((pos - target).get_length() > 1.0f)
    {
      FloatVector2d direction = (target - pos);
      pos += direction * speed;
   }
  
  x_offset = int(pos.x);
  y_offset = int(pos.y);

  float my_rotation = -(vehicle->get_angle ()/3.1415927*180.0) + 90;

  if (rotation > my_rotation) rotation -= 2 * delta;
  if (rotation < my_rotation) rotation += 2 * delta;
}

void
VehicleView::set_vehicle (VehiclePtr arg_vehicle)
{
  vehicle = arg_vehicle;
}

/* EOF */
