//  $Id: scm_functor.hxx,v 1.4 2003/06/03 14:11:22 grumbel Exp $
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

#ifndef HEADER_SCM_FUNCTOR_HXX
#define HEADER_SCM_FUNCTOR_HXX

#include <libguile.h>
#include "sequence_manager.hxx"

/** */
class SCMFunctor
{
private:
  SCM func;
public:
  SCMFunctor(SCM func);
  virtual ~SCMFunctor();

  SCMFunctor(const SCMFunctor&);

  SCMFunctor& operator= (const SCMFunctor&);

  void operator()();
  void operator()(SCM arg);
  void operator()(SCM arg1, SCM arg2);
  void operator()(SCM arg1, SCM arg2, SCM arg3);
};

#endif

/* EOF */
