//  $Id: menu.cxx,v 1.5 2003/06/18 13:03:13 grumbel Exp $
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
#include "assert.hxx"
#include "display_manager.hxx"
#include "fonts.hxx"
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
  CL_Display::fill_rect(CL_Rect(CL_Display::get_width() - 170, 0,
                                CL_Display::get_width(), items.size() 
                                * (Fonts::font.get_height() + 4) + 20),
                        CL_Color(0,0,0, 50));

  // Draw menu items
  int y = 10;
  for(MenuItems::iterator i = items.begin(); i != items.end(); ++i)
    {
      if ((i - items.begin()) == current_item)
        (*i)->draw_highlight(CL_Display::get_width() - 160, y);
      else
        (*i)->draw(CL_Display::get_width() - 160, y);

      y += (Fonts::font.get_height() + 4);
    }
}

void
Menu::next_item()
{
  AssertMsg(items.size() > 0, "Menu is empty!");

  if (current_item == static_cast<int>(items.size()) - 1)
    current_item = 0;
  else
    current_item += 1;
}

void
Menu::previous_item()
{
  AssertMsg(items.size() > 0, "Menu is empty!");

  if (current_item == 0)
    current_item = items.size()-1;
  else
    current_item -= 1;
}

void
Menu::call_current_item()
{
  AssertMsg(items.size() > 0, "Menu is empty!");

  items[current_item]->call();
}

void
Menu::hide()
{
  if (DisplayManager::current()->get_menu() == this)
    DisplayManager::current()->hide_menu();
}

void
Menu::process_events(const InputEventLst& lst)
{
  for(InputEventLst::const_iterator i = lst.begin(); i != lst.end(); ++i)
    {
      switch(i->type)
        {
        case AXIS_EVENT:
          switch (i->axis.name)
            {
            case ACCELERATE_AXIS:
              if (i->axis.pos > 0)
                next_item();
              else if (i->axis.pos < 0)
                previous_item();
              break;
            default:
              break;
            }
          break;
        case BUTTON_EVENT:
          switch (i->button.name)
            {
            case PRIMARY_FIRE_BUTTON:
              if (i->button.down)
                {
                  call_current_item();
                  hide();
                }
              break;
            default:
              break;
            }
          break;
        default:
          break;
        }
    }
}

/* EOF */
