//  $Id: menu_item.cpp,v 1.4 2003/10/31 23:24:41 grumbel Exp $
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

#include <ClanLib/Display/display.h>
#include "fonts.hpp"
#include "display_manager.hpp"
#include "menu_item.hpp"

MenuItemSubMenuFunctor::MenuItemSubMenuFunctor(Menu* arg_submenu)
  : submenu(arg_submenu)
{
}

void
MenuItemSubMenuFunctor::call()
{ // FIXME: This could be implemented on the scheme site
  DisplayManager::current()->push_menu(submenu);
}

MenuItem::MenuItem(const std::string& arg_label, MenuItemFunctor* arg_functor)
  : label(arg_label),
    functor(arg_functor)
{
  
}

MenuItem::~MenuItem()
{
  delete functor;
}

void
MenuItem::draw_highlight(int x, int y)
{
  CL_Display::fill_rect(CL_Rect(x, y, x + 150, y + Fonts::font.get_height() + 2),
                        CL_Color(255, 255, 255, 230));
  Fonts::font.set_alignment(origin_top_left);
  Fonts::font.draw(x + 10, y + 1, label);
}

void
MenuItem::draw(int x, int y)
{
  CL_Display::fill_rect(CL_Rect(x, y, x + 150, y + Fonts::font.get_height() + 2),
                        CL_Color(85,85,0, 230));
  Fonts::font.set_alignment(origin_top_left);
  Fonts::font.draw(x + 10, y + 1, label);
}

void
MenuItem::call()
{
  functor->call();
}

/* EOF */
