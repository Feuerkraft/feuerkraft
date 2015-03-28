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

#include "../scm_functor.hpp"
#include "../sequence_manager.hpp"
#include "sequence_commands.hpp"

int  sequence_start()
{
  return SequenceManager::current()->start_sequence();
}

void sequence_end(int id)
{
  SequenceManager::current()->end_sequence(id);
}

void sequence_add_hook(SCM func)
{
  SequenceManager::current()->add_hook(new GenericSequenceHook<SCMFunctor>(SCMFunctor(func)));
}

/* EOF */
