//  $Id: input_commands.cpp,v 1.5 2003/06/20 20:54:23 grumbel Exp $
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

#include <ClanLib/Display/mouse.h>
#include "../scm_functor.hpp"
#include "../keys.hpp"
#include "../view.hpp"
#include "../keyboard_manager.hpp"
#include "../input/input_manager.hpp"
#include "input_commands.hpp"

void
input_register_callback(const char* key, SCM func)
{
  KeyboardManager::instance()->register_down_callback(string2keyid(key), SCMFunctor(func));
}

int
input_get_mouse_x()
{
  return CL_Mouse::get_x();
}

int
input_get_mouse_y()
{
  return CL_Mouse::get_y();
}

float
input_get_mouse_world_x()
{
  return View::current()->screen_to_world(FloatVector2d(CL_Mouse::get_x(),
                                                        CL_Mouse::get_y())).x;  
}

float
input_get_mouse_world_y()
{
  return View::current()->screen_to_world(FloatVector2d(CL_Mouse::get_x(),
                                                        CL_Mouse::get_y())).y;
}

/* EOF */
