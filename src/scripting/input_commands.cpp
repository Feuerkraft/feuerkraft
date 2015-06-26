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
