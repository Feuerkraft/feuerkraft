//  $Id: command_line_arguments.hxx,v 1.2 2003/05/11 11:20:44 grumbel Exp $
// 
//  Pingus - A free Lemmings clone
//  Copyright (C) 2002 Ingo Ruhnke <grumbel@gmx.de>
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

#ifndef HEADER_FEUERKRAFT_COMMAND_LINE_ARGUMENTS_HXX
#define HEADER_FEUERKRAFT_COMMAND_LINE_ARGUMENTS_HXX

#include <string>

/** */
struct CommandLineArguments
{
public:
  /** Mission file to start, empty() if non is given */
  std::string mission_file;

  /** Path to all the datafiles */
  std::string datadir;

  /** number of fps to which the game should limit itself */
  float fps;

  bool music_enabled;
  bool sound_enabled;

  bool verbose;

  CommandLineArguments();
  CommandLineArguments(int argc, char** argv);

  void load_defaults();
  void parse_arguments(int argc, char** argv);

private:
  error_t parse_option(int key, char *arg, struct argp_state *state);

public:  
  /** Dispatch dummy */
  static error_t parse_option_static(int key, char *arg, struct argp_state *state);
};

#endif

/* EOF */
