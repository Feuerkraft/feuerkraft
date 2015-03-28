//  $Id: vehicle.cpp,v 1.11 2003/10/31 23:24:41 grumbel Exp $
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

#include <iostream>
#include "../input/controller.hpp"
#include "vehicle.hpp"

Vehicle::Vehicle ()
  : ammo (1.0f),
    fuel (1.0f)
{
  acceleration = 0;
  steering = 0;
  strafe_steering = 0;
  firing = false;
  secondary_firing = false;
}

float
Vehicle::get_ammo ()
{
  return ammo;
}

float
Vehicle::get_fuel ()
{
  return fuel;
}

void
Vehicle::refuel (float delta)
{
  fuel += 0.003 * delta;

  if (fuel > 1.0f)
    fuel = 1.0f;
}

void
Vehicle::reload_ammo (float delta)
{
  ammo += 0.003 * delta;

  if (ammo > 1.0f)
    ammo = 1.0f;
}

void
Vehicle::update_controlls(const Controller& controller)
{
  acceleration = -controller.get_axis_state(ACCELERATE_AXIS);
  steering     = controller.get_axis_state(ORIENTATION_AXIS);
  strafe_steering = controller.get_axis_state(STRAFE_AXIS);
  firing       = controller.get_button_state(PRIMARY_FIRE_BUTTON);
  secondary_firing       = controller.get_button_state(SECONDARY_FIRE_BUTTON);
}

/* EOF */
