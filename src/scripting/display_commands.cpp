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

#include "../display_manager.hpp"
#include "display_commands.hpp"

bool
display_levelmap_visible()
{
  return DisplayManager::current()->get_levelmap();
}

void
display_show_levelmap()
{
  DisplayManager::current()->show_levelmap();
}

void
display_hide_levelmap()
{
  DisplayManager::current()->hide_levelmap();
}

void
display_show_help()
{
  DisplayManager::current()->show_help();
}

void
display_hide_help()
{
  DisplayManager::current()->hide_help();
}

/* EOF */
