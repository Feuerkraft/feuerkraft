//  $Id: vehicle_commands.hpp,v 1.7 2003/06/17 22:06:13 grumbel Exp $
// 
//  Feuerkraft - A Tank Battle Game
//  Copyright (C) 2002 Ingo Ruhnke <grumbel@gmx.de>
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

#ifndef HEADER_FEUERKRAFT_VEHICLE_COMMANDS_HXX
#define HEADER_FEUERKRAFT_VEHICLE_COMMANDS_HXX

/** @addtogroup scripting */
//@{

#if 0
void vehicle_set_fuel(int fuel);
int  vehicle_get_fuel();

/** @returns weapon_id */
int  vehicle_get_weapon(int number);

/** Set the given vehicle to the given x,y coordinates */
void vehicle_set_position(int vehicle_handle, int x, int y);
#endif 

/** Find the nearest vehicle to the given coordinates, if the nearest
    vehicle is further away than \a max_distance, it is ignored and 0
    is returned */
int vehicle_find_nearest(float x, float y, float max_distance);

void helicopter_start_or_land(int handle);

//@}

#endif

/* EOF */
