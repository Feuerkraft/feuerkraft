//  $Id: command_line_arguments.cxx,v 1.6 2003/06/03 14:11:22 grumbel Exp $
//
//  Feuerkraft - A Tank Battle Game
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

#include <config.h>
#include <iostream>
#include <stdlib.h>
#include <argp.h>
#include "command_line_arguments.hxx"

const char *argp_program_version     = PACKAGE_STRING;
const char *argp_program_bug_address = "Ingo Ruhnke <grumbel@gmx.de>";

static char doc[] = "Feuerkraft is a tank battle game";

static struct argp_option options[] = {
  {"verbose",  'v', 0,         0,  "Produce verbose output" },
  {"quiet",    'q', 0,         0,  "Produce no output" },
  {"datadir",  'd', 0,         0,  "Set the path to search for gamedata" },
  {"fps",      'f', "FPS",     0,  "Limit of frames per second" },
  {"music",    'm', 0,         0,  "Enable music" },
  {"sound",    's', 0,         0,  "Enable sound" },
  {"geometry", 'g', "WIDTHxHEIGHT", 0,  "Set screen size" },
  { 0 }
};

static struct argp argp = { options, CommandLineArguments::parse_option_static, "MISSIONFILE", doc, 0, 0 };

CommandLineArguments::CommandLineArguments()
{
  load_defaults();
}


CommandLineArguments::CommandLineArguments(int argc, char** argv)
{
  load_defaults();
  parse_arguments(argc, argv);
}

void
CommandLineArguments::load_defaults()
{
  // Default Screen Size
  screen_width  = 800;
  screen_height = 600;

  mission_file = "";
  fps          = 30.0f;
  verbose      = true;
  datadir      = "";
  music_enabled = false;
  sound_enabled = false;
}
  
void
CommandLineArguments::parse_arguments(int argc, char** argv)
{
  argp_parse(&argp, argc, argv, 0, 0, this);
}

error_t
CommandLineArguments::parse_option_static(int key, char *arg, struct argp_state *state)
{ // Dispatch to the CommandLineArguments object
  return static_cast<CommandLineArguments*>(state->input)->parse_option(key, arg, state);
}

error_t
CommandLineArguments::parse_option(int key, char *arg, struct argp_state *state)
{
  switch(key)
    {
    case ARGP_KEY_ARGS:
      break;
    case ARGP_KEY_NO_ARGS:
      break;
    case ARGP_KEY_INIT:
      break;
    case ARGP_KEY_FINI:
      break;
    case ARGP_KEY_END:
      break;
    case ARGP_KEY_SUCCESS:
      break;
    case ARGP_KEY_ERROR:
      std::cout << "ERROR" << std::endl;
      break;
      
    case ARGP_KEY_ARG:
      mission_file = arg;
      break;

    case 'f':
      fps = strtof(arg, 0);
      break;

    case 'V':
      std::cout << PACKAGE_STRING << std::endl;
      exit(EXIT_SUCCESS);
      break;

    case 'v':
      verbose = true;
      break;

    case 'd':
      datadir = arg;
      break;

    case 'q':
      verbose = false;
      break;

    case 'm':
      music_enabled = true;
      break;

    case 's':
      sound_enabled = true;
      break;

    case 'g':
      if (sscanf(arg, "%dx%d", &screen_width, &screen_height) != 2)
        {
          std::cout << "Screen size value incorrect: '" << arg << "'" << std::endl;
          exit(EXIT_FAILURE);
        }
      break;

    default: 
      std::cout << "CommandLineArguments: Unhandled key: " << key << std::endl;
      break;
    }
  return 0;
}

/* EOF */
