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
#include <libguile.h>
#include "scm_sequence_hook.hpp"

SCMSequenceHook::SCMSequenceHook(SCM arg_func)
{
  func = arg_func;
  scm_gc_protect_object(func);
}

SCMSequenceHook::~SCMSequenceHook()
{
  scm_gc_unprotect_object(func);
}

SCMSequenceHook::SCMSequenceHook(const SCMSequenceHook& hook)
{
  func = hook.func;

  scm_gc_protect_object(func);
}

SCMSequenceHook&
SCMSequenceHook::operator= (const SCMSequenceHook& hook)
{
  if (this != &hook)
    {
      scm_gc_unprotect_object(func);

      func = hook.func;

      scm_gc_protect_object(func);
    }
  return *this;
}

void
SCMSequenceHook::call()
{
  std::cout << "SCMSequenceHook::call(): " << get_id() << std::endl;
  scm_call_0(func);
}

/* EOF */
