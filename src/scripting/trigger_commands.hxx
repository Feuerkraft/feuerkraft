//  $Id: trigger_commands.hxx,v 1.4 2003/06/09 20:27:31 grumbel Exp $
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

#ifndef HEADER_TRIGGER_COMMANDS_HXX
#define HEADER_TRIGGER_COMMANDS_HXX

/** @addtogroup scripting */
//@{

/** @brief Register a callback that is called after \a seconds
 *         seconds 
 *  @param seconds  number of seconds that have to pass until the
 *                  callback is called
 *  @param func     procedure taking zero arguments
*/
void trigger_add_timed(float seconds, SCM func);

/** @brief Register a callback that is called once a vehicles enters
 *         the given tile.
 *  @param x    tile x coordinate
 *  @param y    tile y coordinate
 *  @param func Callback taking one argument, which is the id of the
 *              vehicle that triggered the trigger
 */
void trigger_add_tile(int x, int y, SCM func);

void trigger_add_region(int x1, int y1, int x2, int y2, SCM func);

//@}

#endif

/* EOF */
