//  $Id: vehicle_status.cxx,v 1.9 2003/06/08 15:31:27 grumbel Exp $
//
//  Feuerkraft - A Tank Battle Game
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

#include <ClanLib/Display/display.h>
#include "resource_manager.hxx"
#include "player.hxx"
#include "vehicle.hxx"
#include "vehicle_status.hxx"

extern Player* player;

VehicleStatus::VehicleStatus()
  : ammo (resources->get_sprite("feuerkraft/ammo")),
    fuel (resources->get_sprite("feuerkraft/fuel"))
{
  fuel.set_alignment(origin_top_left);
  ammo.set_alignment(origin_top_left);
}

VehicleStatus::~VehicleStatus ()
{
}

void 
VehicleStatus::update (float delta)
{
}

void 
VehicleStatus::draw (CL_GraphicContext& gc)
{
  Vehicle* vehicle = dynamic_cast<Vehicle*>(player->get_current_unit());
  if (vehicle)
    {
      fuel.draw ( 8, CL_Display::get_height() - 8 - 30);
      draw_rect (38, CL_Display::get_height() - 8 - 24, vehicle->get_fuel ());

      ammo.draw ( 8, CL_Display::get_height() - 40 - 30);
      draw_rect (38, CL_Display::get_height() - 40 - 24, vehicle->get_ammo ());
    }
}

void
VehicleStatus::draw_rect (int x_pos, int y_pos, float fill)
{
  CL_Display::fill_rect (CL_Rect(x_pos, y_pos, x_pos + 100, y_pos + 14),
			 CL_Color(0, 0, 0,200));
  if (fill > 0.0)
    CL_Display::fill_rect (CL_Rect(x_pos + 2, y_pos + 2, int(x_pos + (98 * fill)), y_pos + 12),
			   CL_Color(int((1.0 - fill)*255), 
                                    int(255*fill),
                                    0,
                                    200));
}

/* EOF */
