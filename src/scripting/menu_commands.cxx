//  $Id: menu_commands.cxx,v 1.4 2003/06/06 20:55:24 grumbel Exp $
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

#include <iostream>
#include "../scm_functor.hxx"
#include "../menu_handle_mgr.hxx"
#include "../display_manager.hxx"
#include "menu_commands.hxx"

void
menu_show(int menu_id)
{
  Menu* menu = menu_handle_mgr.lookup_by_handle(menu_id);
  if (menu)
    DisplayManager::current()->show_menu(menu);
  else
    std::cout << "Incorrect menu handle: " << menu_id << std::endl;
}

void
menu_hide()
{
  DisplayManager::current()->hide_menu();
}

int
menu_create()
{
  Menu* menu = menu_handle_mgr.create();
  return menu_handle_mgr.lookup_by_object(menu);
}

int
menu_add_item(int menu_id, const char* label, SCM func)
{
  Menu* menu = menu_handle_mgr.lookup_by_handle(menu_id);
  if (menu)
    {
      MenuItem* menu_item = menu_item_handle_mgr.create(label, new MenuItemGenericFunctor<SCMFunctor>(func));
      menu->add_item(menu_item);
      return menu_item_handle_mgr.lookup_by_object(menu_item);
    }
  return -1;
}

int
menu_add_submenu_item(int menu_id, const char* label, int sub_menu_id)
{
  return 0;
}

void
menu_remove_item(int menu_id, int item_id)
{
}

bool
menu_visible()
{
  return DisplayManager::current()->get_menu();
}

/* EOF */
