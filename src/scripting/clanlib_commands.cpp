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

#include "clanlib_commands.hpp"

SCM post_keep_alive_func = SCM_BOOL_F;

SCM  clanlib_get_post_keep_alive_func()
{
  return post_keep_alive_func;
}

void clanlib_set_post_keep_alive_func(SCM func)
{
  if (post_keep_alive_func != func)
    {
      if (post_keep_alive_func != SCM_BOOL_F)
        scm_gc_unprotect_object(post_keep_alive_func);

      post_keep_alive_func = func;
      scm_gc_protect_object(post_keep_alive_func);
    }
}

void clanlib_call_post_keep_alive_func()
{
  if (post_keep_alive_func != SCM_BOOL_F)
    {
      gh_call0(post_keep_alive_func);
    }
}

/* EOF */
