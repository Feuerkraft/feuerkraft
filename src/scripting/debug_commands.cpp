//  $Id: debug_commands.cpp,v 1.1 2003/06/18 13:04:21 grumbel Exp $
//
//  Pingus - A free Lemmings clone
//  Copyright (C) 2002 Ingo Ruhnke <grumbel@gmx.de>
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//  
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//  
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include <string.h>
#include <stdexcept>
#include <iostream>
#include "../globals.hpp"
#include "debug_commands.hpp"

static
bool& debug_lookup_flag(const char* name)
{
  if (strcmp(name, "colmap") == 0)
    {
      return draw_colmap;
    }
  else
    {
      throw std::domain_error("Debug: Unknown flag " + std::string(name));
    }
}

void
debug_set_flag(const char* name, bool value)
{
  try 
    {
      debug_lookup_flag(name) = value;
    } 
  catch (std::domain_error& err) 
    {
      std::cout << err.what() << std::endl;
    }
}

bool
debug_get_flag(const char* name)
{
  try 
    {
      return debug_lookup_flag(name);
    } 
  catch (std::domain_error& err) 
    {
      std::cout << err.what() << std::endl;
      return false;
    }
}

/* EOF */
