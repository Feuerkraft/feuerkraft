//  $Id: menu.cxx,v 1.1 2003/06/05 21:17:11 grumbel Exp $
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
#include "menu_item.hxx"
#include "menu.hxx"

Menu::Menu()
{
  current_item = 0;
}

Menu::~Menu()
{
}

void
Menu::add_item(MenuItem* item)
{
  items.push_back(item);
}

void
Menu::update(float delta)
{
  
}

void
Menu::draw(CL_GraphicContext& gc)
{
  // Draw menu background 
  CL_Display::fill_rect(CL_Rect(CL_Display::get_width() - 120, 0,
                                CL_Display::get_width(), items.size() * 25 + 20),
                        CL_Color(0,0,0, 50));

  // Draw menu items
  int y = 10;
  for(MenuItems::iterator i = items.begin(); i != items.end(); ++i)
    {
      if ((i - items.begin()) == current_item)
        (*i)->draw_highlight(CL_Display::get_width() - 110, y);
      else
        (*i)->draw(CL_Display::get_width() - 110, y);
      y += 25;
    }
}

/* EOF */
