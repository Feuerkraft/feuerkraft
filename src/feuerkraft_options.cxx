//  $Id: feuerkraft_options.cxx,v 1.3 2003/06/03 14:11:22 grumbel Exp $
//
//  Feuerkraft - A Tank Battle Game
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

#include "feuerkraft_options.hxx"

FeuerkraftOptions::FeuerkraftOptions ()
{
  // Set defaults for all options
  screen_width  = 800;
  screen_height = 600;
  joystick      = -1;

  // FIXME: This needs to be more flexible of course
  config_file = "/home/ingo/.feuerkraft/config";
}

FeuerkraftOptions::~FeuerkraftOptions ()
{
}

void
FeuerkraftOptions::parse_args (int argc, char** argv)
{
  // add getopt_long parser here
}

void
FeuerkraftOptions::parse_config_file (const std::string& filename)
{
}

bool
FeuerkraftOptions::show_intro ()
{
  return false;
}

bool
FeuerkraftOptions::show_outro ()
{
  return false;
}

int
FeuerkraftOptions::get_screen_width ()
{
  return 800;
}

int
FeuerkraftOptions::get_screen_height ()
{
  return 600;
}
  
std::string
FeuerkraftOptions::get_config_file ()
{
  return config_file;
}

/* EOF */
