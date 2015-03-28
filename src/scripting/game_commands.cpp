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

#include <iostream>
#include "../game_session_manager.hpp"
#include "game_commands.hpp"

void
game_pause()
{
  GameSessionManager::instance()->pause();
}

void
game_quit()
{
  GameSessionManager::instance()->quit();
}

void
game_load(const char* filename)
{
  GameSessionManager::instance()->load(filename);
}

void
game_save(const char* filename)
{
  GameSessionManager::instance()->save(filename);
}

/* EOF */
