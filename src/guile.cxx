//  $Id: guile.cxx,v 1.7 2003/05/10 22:41:28 grumbel Exp $
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
  cl_assert(gh_string_p(data));

  char* tmpstr = gh_scm2newstr(data, 0);
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

std::string keyword2string(SCM keyword)
{
  assert(SCM_KEYWORDP(keyword));
  puts("keyword2string: ");
  gh_display(keyword);
  gh_newline();
  //gh_display(scm_keyword_dash_symbol(keyword));
  //gh_newline();

  char* str = gh_symbol2newstr(scm_keyword_dash_symbol(keyword), 0);
  std::string ret = str + 1; // skip the dash
  free(str);
  return ret;
}

AList scm2alist(SCM lst)
{
  AList alist;
  while(!gh_null_p(lst))
    {
      SCM key  = gh_caar(lst);
      SCM data = gh_cdar(lst);

      if (!gh_symbol_p(key))
        {
          std::cout << "Guile: Error: key not a symbol" << std::endl;
          gh_display(key);
          gh_newline();
        }
      else
        {
          if (gh_string_p(data))
            {
              alist.set_string(Guile::scm2string(key), 
                               Guile::scm2string(data));
            }
          else if (gh_exact_p(data))
            {
              alist.set_int(Guile::scm2string(key), 
                            gh_scm2int(data));
            }
          else if (gh_inexact_p(data))
            {
              alist.set_float(Guile::scm2string(key), 
                              gh_scm2double(data));
            }
          else if (gh_boolean_p(data))
            {
              alist.set_bool(Guile::scm2string(key), 
                             gh_scm2bool(data));
            }
          else
            {
              std::cout << "Guile: Error: Couldn't handle data" << std::endl;
              gh_display(data);
              gh_newline();
            }
        }
    }
  return alist;
}

std::string symbol2string(SCM symbol)
{
  char* c_str = gh_symbol2newstr(symbol, 0);
  std::string str = c_str;
  free(c_str);
  return str;
}

} // namespace Guile

/* EOF */
