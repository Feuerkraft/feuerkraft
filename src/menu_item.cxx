//  $Id: menu_item.cxx,v 1.1 2003/06/05 21:17:11 grumbel Exp $
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
#include "fonts.hxx"
#include "menu_item.hxx"

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
  CL_Display::fill_rect(CL_Rect(x, y, x + 100, y + 20),
                        CL_Color(255, 255, 255, 200));
  Fonts::font.set_alignment(origin_top_left);
  Fonts::font.draw(x + 10, y, label);
}

void
MenuItem::draw(int x, int y)
{
  CL_Display::fill_rect(CL_Rect(x, y, x + 100, y + 20),
                        CL_Color(150,150,150, 155));
  Fonts::font.set_alignment(origin_top_left);
  Fonts::font.draw(x + 10, y, label);
}

/* EOF */
