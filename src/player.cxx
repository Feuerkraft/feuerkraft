//  $Id: player.cxx,v 1.1 2003/05/19 10:55:05 grumbel Exp $
//
//  Pingus - A free Lemmings clone
//  Copyright (C) 2002 Ingo Ruhnke <grumbel@gmx.de>
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

#include "player.hxx"

Player::Player(Vehicle* arg_vehicle)
{
  set_current_vehicle(arg_vehicle);
}

void
Player::set_current_vehicle(Vehicle* arg_vehicle)
{
  vehicle = arg_vehicle;
}

Vehicle*
Player::get_current_vehicle()
{
  return vehicle;
}

/* EOF */
