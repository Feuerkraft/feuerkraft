//  $Id: guile.hxx,v 1.1 2003/04/19 22:39:06 grumbel Exp $
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

#ifndef GUILE_HXX
#define GUILE_HXX

#include <guile/gh.h>
#include <ClanLib/core.h>
#include <string>
#include <iostream>

/** A loose collection of Guile helper functions */
class Guile
{
private:

public:
  /** Convert a scheme string into a C++ std::string, converting other
      non string SCM data isn't currently supported */
  static std::string scm2string (SCM data);

  /** Convert a CL_Vector into a SCM of the form (pos 12.2 40.912 234) */
  static SCM vector2scm (const CL_Vector& vec);

  /** Used in the BuildingMap: x,y => (pos x y) */
  static SCM pos2scm (int x, int y);

  static SCM symbol_value_pair (const std::string&, float);

  /** Pretty print the object given by obj */
  static void pretty_print (std::ostream& s, SCM obj);

};

#endif

/* EOF */
