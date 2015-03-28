//  $Id: menu_handle_mgr.hpp,v 1.1 2003/06/06 09:49:35 grumbel Exp $
//
//  Pingus - A free Lemmings clone
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

#ifndef HEADER_MENU_HANDLE_MGR_HXX
#define HEADER_MENU_HANDLE_MGR_HXX

#include "menu.hpp"
#include "menu_item.hpp"
#include "handle_manager.hpp"

extern HandleManager<Menu>     menu_handle_mgr;
extern HandleManager<MenuItem> menu_item_handle_mgr;

#endif

/* EOF */
