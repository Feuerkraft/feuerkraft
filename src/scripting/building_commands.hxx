//  $Id: building_commands.hxx,v 1.5 2003/05/14 08:48:48 grumbel Exp $
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

#ifndef HEADER_BUILDING_COMMONDS_HXX
#define HEADER_BUILDING_COMMONDS_HXX

/** @addtogroup scripting */
//@{

/** Create a building from type \a type at the tile position x, y
    @return a handler to the building */
int  building_create(int type, int x, int y);

SCM  building_get_property(int handle, const char* name);
void building_set_property(int handle, const char* name, SCM value);

/** Remove the given building */
void building_remove(int handle);

/** @return the building at the given tile */
int  building_get_tile(int x, int y);

/** @return the building at the given coordinates */
int  building_get(int x, int y);

int  building_create_type(const char* name, SCM lst);

/*@}*/

#endif

/* EOF */
