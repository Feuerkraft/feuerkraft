//  $Id: menu_commands.hxx,v 1.3 2003/06/06 20:55:24 grumbel Exp $
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

#ifndef HEADER_MENU_COMMANDS_HXX
#define HEADER_MENU_COMMANDS_HXX

#include <libguile.h>

/** Create an empty menu
    @return menu_id of the newly created menu */
int menu_create();

/** Display the menu given by \a menu_id on the screen, hide any other
    menu that might currently be visible */
void menu_show(int menu_id);

/** Hide the currently visible menu */
void menu_hide();

bool menu_visible();

/** @return item_id */
int  menu_add_item(int menu_id, const char* label, SCM func);

/** Add a menu item that links to a submenu */
int  menu_add_submenu_item(int menu_id, const char* label, int sub_menu_id);

/** Remove an item from a menu */
void menu_remove_item(int menu_id, int item_id);


#endif

/* EOF */
