//  $Id: sequence_manager.cxx,v 1.1 2003/05/02 00:17:14 grumbel Exp $
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

#include <iostream>
#include "sequence_manager.hxx"

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
