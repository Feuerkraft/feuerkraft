//  $Id: Pathfinder.cc,v 1.2 2001/04/27 19:43:15 grumbel Exp $
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

#ifndef WIN32
#  include <unistd.h>
#endif 

#include <iostream>
#include <string>

#include "System.hh"
#include "Pathfinder.hh"

Pathfinder::Pathfinder ()
{
#ifdef WIN32
  path_seperator = '\\';
#else
  path_seperator = '/';
#endif
}

Pathfinder::~Pathfinder ()
{
}
  
std::string
Pathfinder::trim (std::string str)
{
  if (str.empty ())
    return "";
  
  for (std::string::size_type i = 0; i < str.length (); ++i)
    {
      if (str[i] == '/')
	str[i] = path_seperator;
    }

  if (str[str.length () - 1] == '/')
    return str.substr (0, str.length () - 2);
  
  return str;
}

void 
Pathfinder::add_sig_files (const std::string& str)
{
  significant_files.push_back (str);
}

void 
Pathfinder::add_front (const std::string& str)
{
  paths.push_front (trim(str));
}

void 
Pathfinder::add_back (const std::string& str)
{
  paths.push_front (trim(str));
}

void
Pathfinder::print ()
{
  std::cout << "--------------------------------------------" << std::endl;
  std::cout << "Paths: " << std::endl;

  for (PathIter i = paths.begin (); i != paths.end (); ++i)
    {
      std::cout << "  " << *i << std::endl;
    }
  std::cout << "--------------------------------------------" << std::endl;  
}

std::string 
Pathfinder::find (const std::string& str)
{
  return find_path (str) + path_seperator + str;
}

std::string 
Pathfinder::find_path (const std::string& str)
{
  std::string full_path;
  
  for (PathIter i = paths.begin (); i != paths.end (); ++i)
    {
      full_path = *i + path_seperator + str;

      if (System::exist (full_path))
	{
	  return *i;
	}
    }

  throw FileNotFound (str);
}

/* EOF */
