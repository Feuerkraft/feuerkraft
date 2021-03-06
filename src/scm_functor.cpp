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
#include "scm_functor.hpp"

SCMFunctor::SCMFunctor(SCM arg_func)
{
  func = arg_func;
  scm_gc_protect_object(func);
}

SCMFunctor::~SCMFunctor()
{
  scm_gc_unprotect_object(func);
}

SCMFunctor::SCMFunctor(const SCMFunctor& hook)
{
  func = hook.func;

  scm_gc_protect_object(func);
}

SCMFunctor&
SCMFunctor::operator= (const SCMFunctor& hook)
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
SCMFunctor::operator()()
{
  scm_call_0(func);
}

void
SCMFunctor::operator()(SCM arg)
{
  scm_call_1(func, arg);
}

void
SCMFunctor::operator()(SCM arg1, SCM arg2)
{
  scm_call_2(func, arg1, arg2);
}

void
SCMFunctor::operator()(SCM arg1, SCM arg2, SCM arg3)
{
  scm_call_3(func, arg1, arg2, arg3);
}

/* EOF */
