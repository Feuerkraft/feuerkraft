//  $Id: vehicle_commands.hxx,v 1.4 2003/06/03 14:11:22 grumbel Exp $
// 
//  Feuerkraft - A Tank Battle Game
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

#ifndef HEADER_FEUERKRAFT_VEHICLE_COMMANDS_HXX
#define HEADER_FEUERKRAFT_VEHICLE_COMMANDS_HXX

void vehicle_set_fuel(int fuel);
int  vehicle_get_fuel();

/** @returns weapon_id */
int  vehicle_get_weapon(int number);

/** Set the given vehicle to the given x,y coordinates */
void vehicle_set_position(int vehicle_handle, int x, int y);

/** Find the nearest vehicle to the given coordinates, if the nearest
    vehicle is further away than \a max_distance, it is ignored and 0
    is returned */
int vehicle_find_nearest(float x, float y, float max_distance);

#endif

/* EOF */
