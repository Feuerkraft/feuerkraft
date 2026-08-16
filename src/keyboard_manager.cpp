// Feuerkraft - A Tank Battle Game
// Copyright (C) 2002 Ingo Ruhnke <grumbel@gmail.com>
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

#include "keyboard_manager.hpp"

KeyboardManager* KeyboardManager::instance_ = 0;

KeyboardManager::KeyboardManager()
  : callbacks()
{
}

KeyboardManager::~KeyboardManager()
{
  for (Callbacks::iterator i = callbacks.begin(); i != callbacks.end(); ++i)
    delete *i;
}

void
KeyboardManager::on_key_down(int key_id)
{
  for (Callbacks::iterator i = callbacks.begin(); i != callbacks.end(); ++i)
    {
      if ((*i)->key_id == key_id)
        (*i)->run();
    }
}

void
KeyboardManager::on_key_up(int /*key_id*/)
{
}

/* EOF */
