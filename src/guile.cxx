//  $Id: guile.cxx,v 1.4 2003/05/03 16:21:35 grumbel Exp $
//
//  Pingus - A free Lemmings clone
//  Copyright (C) 2000 Ingo Ruhnke <grumbel@gmx.de>
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

#include <guile/gh.h>
#include <ClanLib/Core/System/cl_assert.h>

#include "guile.hxx"

namespace Guile {
std::string
scm2string (SCM data)
{
  cl_assert(SCM_STRINGP(data));

  char* tmpstr = gh_scm2newstr(SCM_CADR(data), 0);
  std::string str = tmpstr;

#ifdef WIN32 // the free causes throuble on Win32, so we disable it
  free (tmpstr);
#endif

  return str;
}

SCM vector2scm (const CL_Vector& vec)
{
  /** If this causes throuble on WIN32, replace it with gh_cons() */
  return SCM_BOOL_F; /*scm_listify (gh_symbol2scm ("pos"),
                      gh_double2scm(vec.x),
                      gh_double2scm(vec.y),
                      gh_double2scm(vec.z),
                      SCM_UNDEFINED);*/
}

SCM pos2scm (int x, int y)
{
  return SCM_BOOL_F;/*scm_listify (gh_symbol2scm ("pos"),
                      gh_int2scm (x),
                      gh_int2scm (y), 
                      SCM_UNDEFINED);*/
}

void pretty_print (std::ostream& stream, SCM obj)
{
  std::cout << "pretty_print" << std::endl;
  // FIXME: ...lalala..
  gh_write (obj);
  gh_newline ();

}

bool equal_p(SCM a, SCM b)
{
  return SCM_NFALSEP(scm_equal_p(a, b));
}

SCM symbol2scm(const char* str)
{
  return scm_str2symbol(str);
}

} // namespace Guile

/* EOF */
