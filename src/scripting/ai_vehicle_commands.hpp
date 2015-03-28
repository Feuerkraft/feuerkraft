//  $Id: ai_vehicle_commands.hpp,v 1.5 2003/06/03 14:11:22 grumbel Exp $
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

#ifndef HEADER_AI_VEHICLE_COMMANDS_HXX
#define HEADER_AI_VEHICLE_COMMANDS_HXX

/** @addtogroup scripting */
//@{

/**
 * @brief Create a vehicle at the given coordinates
 *
 * @param x  x coordinate in world-coordinates
 * @param y  y coordinate in world-coordinates
 *
 * @return id of the vehicle
 */
int  ai_vehicle_create(int x, int y);

/**
 * @brief Order an vehicle to wait before doing the next order
 *
 * @param object_id  id of the object to which the command should go
 * @param seconds    let the vehicle wait \a seconds seconds before
 *                   continuing with the next order
 */
void ai_vehicle_wait(int object_id, float seconds);

/**
 * @brief Order a vehicle to drive to the given world coordinates
 *
 * @param object_id
 * @param x
 * @param y
 */
void ai_vehicle_drive_to(int object_id, int x, int y);

/**
 * @brief Remove all current orders that a vehicle has accumulated
 *
 * @param object_id id of the vehicle that should get the order
 *
 * The vehicle will halt immediately after the command has been given
 */
void ai_vehicle_clear_orders(int object_id);

//@}

#endif

/* EOF */
