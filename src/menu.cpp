//  $Id: menu.cpp,v 1.7 2003/10/31 23:24:41 grumbel Exp $
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

#include <ClanLib/Display/display.h>
#include "assert.hpp"
#include "display_manager.hpp"
#include "fonts.hpp"
#include "input/input_manager.hpp"
#include "menu_item.hpp"
#include "menu.hpp"

Menu::Menu()
{
  current_item = 0;
  pos = 0;
  moving = false;
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
              // not using events for analog, but states
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
                  std::cout << "--- button event" << std::endl;
                  call_current_item();
                  hide();
                }
              break;
            case SECONDARY_FIRE_BUTTON:
              // FIXME: Go a menu item back (hack)
              DisplayManager::current()->pop_menu();
              break;
            default:
              break;
            }
          break;
        default:
          break;
        }
    }

  // FIXME: no delta
  float delta = InputManager::get_controller().get_axis_state(ACCELERATE_AXIS);

  if (delta > .1f && !moving)
    {
      pos = 5.0f;
      moving = true;
    }
  else if (delta < -.1f && !moving)
    {
      pos = -5.0f;
      moving = true;
    }
  else if (moving && fabsf(delta) < .1f)
    {
      moving = false;
    }

  pos += delta/4.0f;

  if (pos >= 1.0f)
    {
      next_item();
      pos = 0.0f;
    }
  else if (pos <= -1.0f)
    {
      previous_item();
      pos = 0.0f;
    }
}

/* EOF */
