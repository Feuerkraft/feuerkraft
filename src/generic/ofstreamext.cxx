//  $Id: ofstreamext.cxx,v 1.3 2003/05/13 17:30:27 grumbel Exp $
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

#include "ofstreamext.hxx"

/*
std::ostream& operator<<(std::ostream& s, const CL_Vector& pos)
{
  return (s << "(pos: " << pos.x << ", " << pos.y << ", " << pos.z << ")");
}*/

/*std::ostream& operator<<(std::ostream& s, SCM desc)
{
  //FIXME: This is for guile1.5
  //SCM str = scm_object_to_string (desc); // FIXME: Will this gets garbage collected?

  SCM str = scm_strprint_obj (desc);
  return (s << SCM_CHARS(str));
}*/

/* EOF */
