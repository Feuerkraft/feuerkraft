//  $Id: vehicle_status.cxx,v 1.1 2003/04/19 22:39:07 grumbel Exp $
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

#include "ResourceManager.hxx"
#include "VehicleStatus.hxx"

VehicleStatus::VehicleStatus (boost::dummy_ptr<Vehicle> v)
  : ammo (resources->get_sprite("feuerkraft/ammo")),
    fuel (resources->get_sprite("feuerkraft/fuel")),
    vehicle (v)
{
}

VehicleStatus::~VehicleStatus ()
{
}

void 
VehicleStatus::update (float delta)
{
}

void 
VehicleStatus::draw (CL_GraphicContext* gc)
{
  fuel.draw (8, 600 - 8 - 30, gc);
  draw_rect (38, 600 - 8 - 24, vehicle->get_fuel ());

  ammo.draw (8, 600 - 40 - 30, gc);
  draw_rect (38, 600 - 40 - 24, vehicle->get_ammo ());
}

void
VehicleStatus::draw_rect (int x_pos, int y_pos, float fill)
{
  //FIXME:Display2: frame support removed 
  /*
  CL_Display::fill_rect (CL_Rect(x_pos, y_pos, x_pos + 100, y_pos + 14),
			 CL_Color(0, 0, 0));
  if (fill > 0.0)
    CL_Display::fill_rect (x_pos + 2, y_pos + 2, int(x_pos + (98 * fill)), y_pos + 12,
			   1.0 - fill, fill, 0.0);
  */
}

/* EOF */
