//  $Id: scm_sequence_hook.cxx,v 1.2 2003/06/03 14:11:22 grumbel Exp $
//
//  Feuerkraft - A Tank Battle Game
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
#include <libguile.h>
#include "scm_sequence_hook.hxx"

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
