//  $Id: menu_commands.cpp,v 1.7 2003/10/31 23:24:41 grumbel Exp $
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

#include <iostream>
#include "../scm_functor.hpp"
#include "../menu_handle_mgr.hpp"
#include "../display_manager.hpp"
#include "menu_commands.hpp"

void
menu_show(int menu_id)
{
  Menu* menu = menu_handle_mgr.lookup_by_handle(menu_id);
  if (menu)
    DisplayManager::current()->push_menu(menu);
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
      MenuItem* menu_item = menu_item_handle_mgr.create("- " + std::string(label),
                                                        new MenuItemGenericFunctor<SCMFunctor>(func));
      menu->add_item(menu_item);
      return menu_item_handle_mgr.lookup_by_object(menu_item);
    }
  return -1;
}

int
menu_add_submenu_item(int menu_id, const char* label, int sub_menu_id)
{
  Menu* menu     = menu_handle_mgr.lookup_by_handle(menu_id);
  Menu* sub_menu = menu_handle_mgr.lookup_by_handle(sub_menu_id);

  if (menu && sub_menu)
    {
      MenuItem* menu_item = menu_item_handle_mgr.create("+ " + std::string(label), 
                                                        new MenuItemSubMenuFunctor(sub_menu));
      menu->add_item(menu_item);
      return menu_item_handle_mgr.lookup_by_object(menu_item);
    }
  else
    {
      std::cout << __FUNCTION__ << ": Invalid menu id: " << menu_id << " " << sub_menu_id << std::endl;
      return 0;
    }
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
