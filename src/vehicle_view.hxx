//  $Id: vehicle_view.hxx,v 1.7 2003/05/19 10:52:48 grumbel Exp $
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

#ifndef VEHICLEVIEW_HH
#define VEHICLEVIEW_HH

#include "vehicle.hxx"
#include "view.hxx"

class VehicleView 
  : public View
{
private:
  VehiclePtr vehicle;
  FloatVector2d pos;

  float speed;
  float zoom_follower;
public:
  VehicleView (int x1, int y1, int x2, int y2,
               VehiclePtr arg_vehicle);
  virtual ~VehicleView ();

  void set_vehicle (VehiclePtr arg_vehicle);
  virtual void update (float delta);
};

typedef VehicleView* VehicleViewPtr;

#endif

/* EOF */
