//  $Id: VehicleView.cc,v 1.2 2001/02/24 21:32:04 grumbel Exp $
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

#include "VehicleView.hh"

VehicleView::VehicleView (GameWorld* world,
			  Vehicle* arg_vehicle, 
			  int x1, int y1, int x2, int y2) :
  View (world, x1, y1, x2, y2,
	-arg_vehicle->get_pos ().x, -arg_vehicle->get_pos ().y),
  vehicle (arg_vehicle)
{
  
}

VehicleView::~VehicleView ()
{
}

void 
VehicleView::update ()
{
  x_offset = int(vehicle->get_pos ().x);
  y_offset = int(vehicle->get_pos ().y);

  //std::cout << "Offset: " << x_offset << " " << y_offset << std::endl;
}

/* EOF */
