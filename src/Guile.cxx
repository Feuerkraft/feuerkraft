//  $Id: Guile.cxx,v 1.2 2002/04/07 16:58:34 sphair Exp $
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

#include "Guile.hxx"

std::string
Guile::scm2string (SCM data)
{
  cl_assert (gh_string_p (data));

  char* tmpstr = gh_scm2newstr(gh_cadr (data), 0);
  std::string str = tmpstr;

#ifdef WIN32 // the free causes throuble on Win32, so we disable it
  free (tmpstr);
#endif

  return str;
}

SCM
Guile::vector2scm (const CL_Vector& vec)
{
  /** If this causes throuble on WIN32, replace it with gh_cons() */
  return gh_list (gh_symbol2scm ("pos"),
		  gh_double2scm(vec.x),
		  gh_double2scm(vec.y),
		  gh_double2scm(vec.z),
		  SCM_UNDEFINED);
}

SCM
Guile::pos2scm (int x, int y)
{
  return gh_list (gh_symbol2scm ("pos"),
		  gh_int2scm (x),
		  gh_int2scm (y), 
		  SCM_UNDEFINED);
}

void
Guile::pretty_print (ostream& stream, SCM obj)
{
  std::cout << "Guile::pretty_print" << std::endl;
  // FIXME: ...lalala..
  gh_write (obj);
  gh_newline ();
}

/* EOF */
