//  $Id: vehicle.cxx,v 1.2 2003/04/19 23:17:52 grumbel Exp $
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

#include "vehicle.hxx"

Vehicle::Vehicle (boost::dummy_ptr<GameWorld>  w)
  : Collideable (w),
    ammo (1.0f), 
    fuel (1.0f)
{
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

/* EOF */
