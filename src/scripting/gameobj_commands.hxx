//  $Id: gameobj_commands.hxx,v 1.2 2003/05/19 10:52:48 grumbel Exp $
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

#ifndef HEADER_GAMEOBJ_COMMANDS_HXX
#define HEADER_GAMEOBJ_COMMANDS_HXX

#include <guile/gh.h>

SCM  gameobj_get_property(int handle, const char* name);
void gameobj_set_property(int handle, const char* name, SCM value);

/** @return a list of available properties */
SCM gameobj_properties(int handle);

/** Create a game object with the parameters given as \a lst 
    @return handle to the GameObj */
int gameobj_create(int type_id, SCM lst);

#endif

/* EOF */
