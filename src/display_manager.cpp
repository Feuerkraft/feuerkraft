// Feuerkraft - A Tank Battle Game
// Copyright (C) 2002 Ingo Ruhnke <grumbel@gmx.de>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include <ClanLib/Display/display.h>
#include "assert.hpp"
#include "help.hpp"
#include "radar.hpp"
#include "menu.hpp"
#include "level_map.hpp"
#include "vehicle_status.hpp"
#include "message_buffer.hpp"
#include "communication_dialog.hpp"
#include "display_manager.hpp"

extern Player*  player;
DisplayManager* DisplayManager::current_ = 0;

void
DisplayManager::init()
{
  AssertMsg(current_ == 0, "DisplayManager already initialized, this must not be done more than once!");
  current_ = new DisplayManager();
}

void
DisplayManager::deinit()
{
  delete current_;
}

DisplayManager::DisplayManager()
{
  level_map = new LevelMap();

  screen.add(message_buffer = new MessageBuffer(CL_Display::get_width()/2, CL_Display::get_height() - 30));
  help = new Help();
  screen.add(radar = new Radar(FloatVector2d(64, 64), player));
  screen.add(new CommunicationDialog());
  screen.add(vehicle_status = new VehicleStatus());
}

DisplayManager::~DisplayManager()
{
}

void
DisplayManager::add(GuiObj* obj)
{
  screen.add(obj);
}

void
DisplayManager::update(float delta)
{
  screen.update(delta);
}

void
DisplayManager::draw(CL_GraphicContext& gc)
{
  screen.draw(gc);
}

void
DisplayManager::show_levelmap()
{
  screen.add(level_map);
}

void
DisplayManager::hide_levelmap()
{
  screen.remove(level_map);
}

LevelMap*
DisplayManager::get_levelmap()
{
  if (screen.has(level_map))
    return level_map;
  else
    return 0;
}

void
DisplayManager::show_help()
{
  screen.add(help);
}

void
DisplayManager::hide_help()
{
  screen.remove(help);
}

void
DisplayManager::push_menu(Menu* arg_menu)
{
  //hide_menu(); // Hide current menu
  if (!menu.empty())
    {
      screen.remove(menu.back());
    }

  menu.push_back(arg_menu);
  screen.add(arg_menu);
}

void
DisplayManager::pop_menu()
{
  if (!menu.empty())
    {
      screen.remove(menu.back());
      menu.pop_back();
      if (!menu.empty())
        {
          screen.add(menu.back());
        }
    }
}

void
DisplayManager::hide_menu()
{
  if (!menu.empty())
    {
      for (Menus::iterator i = menu.begin(); i != menu.end(); ++i)
        screen.remove(*i);
      menu.clear();
    }
}

/* EOF */
