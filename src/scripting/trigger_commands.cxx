//  $Id: trigger_commands.cxx,v 1.1 2003/05/02 14:28:26 grumbel Exp $
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

#include "../timed_trigger_manager.hxx"
#include "../scm_functor.hxx"
#include "trigger_commands.hxx"

// FIXME: return handles to the triggers to allow removal of them

void
trigger_add_timed(float seconds, SCM func)
{
  TimedTriggerManager::current()->add_trigger(seconds, SCMFunctor(func));
}

void
trigger_add_tile(int x, int y, SCM func)
{
}

void
trigger_add_region(int x1, int y1, int x2, int y2, SCM func)
{
}

/* EOF */
