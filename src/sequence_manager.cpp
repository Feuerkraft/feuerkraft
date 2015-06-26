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

#include <iostream>
#include "sequence_manager.hpp"

SequenceManager* SequenceManager::current_ = 0;

SequenceHook::SequenceHook()
{

}

void
SequenceHook::call()
{
  std::cout << "SequenceHook: " << id << " called" << std::endl;
}

SequenceManager::SequenceManager()
{
  current_sequence_id = 0;
}

int
SequenceManager::start_sequence()
{
  ++current_sequence_id;

  return current_sequence_id;
}

void
SequenceManager::end_sequence(int sequence_id)
{
  //std::cout << "Calling hook with id: " << current_sequence_id << " " << hooks.size() << std::endl;
  for (Hooks::iterator i = hooks.begin(); i != hooks.end(); ++i)
    {
      if ((*i)->get_id() == sequence_id)
        {
          (*i)->call();
        }
    }
}

void
SequenceManager::add_hook(SequenceHook* hook)
{
  std::cout << "Adding hook with id: " << current_sequence_id << std::endl;
  hook->set_id(current_sequence_id);
  hooks.push_back(hook);
}

/* EOF */
