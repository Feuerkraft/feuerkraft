// Feuerkraft - A Tank Battle Game
// Copyright (C) 2002 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#ifndef HEADER_INPUT_COMMANDS_HXX
#define HEADER_INPUT_COMMANDS_HXX

/** @addtogroup scripting */
//@{

/** @brief Register a callback on a key press event
 *  @param key   a string representing the key, see keys.hpp
 *  @param func  a procedure taking zero arguments
 *
 *  Currently this is a bit limited and buggy, mouse events and other
 *  input events might also be grabbed when the correct string is
 *  \a key string supplied.
 */
void input_register_callback(const char* key, SCM func);

/** @brief Return the current mouse x position on the screen */
int  input_get_mouse_x();

/** @brief Return the current mouse y position on the screen  */
int  input_get_mouse_y();

/** Return the current mouse x position on the world */
float input_get_mouse_world_x();
/** Return the current mouse y position on the world */
float input_get_mouse_world_y();

//@}

#endif

/* EOF */
