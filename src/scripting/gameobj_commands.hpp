// Feuerkraft - A Tank Battle Game
// Copyright (C) 2002 Ingo Ruhnke <grumbel@gmx.de>
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

#ifndef HEADER_GAMEOBJ_COMMANDS_HXX
#define HEADER_GAMEOBJ_COMMANDS_HXX

#include <guile/gh.h>

/** @addtogroup scripting */
//@{

SCM  gameobj_get_property(int handle, const char* name);
void gameobj_set_property(int handle, const char* name, SCM value);

/** @return a list of available properties */
SCM gameobj_properties(int handle);

/** Create a game object with the parameters given as \a lst
    @return handle to the GameObj */
int gameobj_create(int type_id, SCM lst);

/** Remove the game object given by \a handle from the world */
void gameobj_remove(int handle);

/** @return a list of all gameobjects */
SCM  gameobj_get_all();

bool gameobj_is_helicopter(int handle);
bool gameobj_is_vehicle(int handle);
bool gameobj_is_unit(int handle);
bool gameobj_is_soldier(int handle);

void satchel_detonate(int handle);

//@}

#endif

/* EOF */
