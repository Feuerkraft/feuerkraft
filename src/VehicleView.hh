//  $Id: VehicleView.hh,v 1.3 2001/05/04 17:11:08 grumbel Exp $
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

#include "boost/dummy_ptr.hpp"
#include "Vehicle.hh"
#include "View.hh"

class VehicleView :
  public View
{
private:
  boost::dummy_ptr<Vehicle> vehicle;
  CL_Vector pos;
  float speed;
  
public:
  VehicleView (boost::dummy_ptr<GameWorld>
 world, 
	       boost::dummy_ptr<Vehicle> arg_vehicle, 
	       int x1, int y1, int x2, int y2);
  virtual ~VehicleView ();
  
  void update (float delta);
};

#endif

/* EOF */
