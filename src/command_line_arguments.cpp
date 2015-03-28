// Feuerkraft - A Tank Battle Game
// Copyright (C) 2002 Ingo Ruhnke <grumbel@gmx.de>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <ClanLib/Core/System/command_line.h>

#include "command_line_arguments.hpp"

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
  fullscreen    = false;

  mission_file = "";
  fps          = 30.0f;
  joystick     = -1;
  verbose      = true;
  datadir      = "";
  music_enabled = false;
  sound_enabled = false;
}

void
CommandLineArguments::parse_arguments(int argc, char** argv)
{
  CL_CommandLine argp;

  argp.set_help_indent(22);
  argp.add_usage ("[LEVELFILE]");
  argp.add_doc   ("Feuerkraft is a tank battle game");

  argp.add_group("General Options:");
  argp.add_option('v', "verbose", "",  "Produce verbose output");
  argp.add_option('V', "version", "",  "Print the exact version of the game");
  argp.add_option('q', "quiet",   "",  "Produce no output");
  argp.add_option('h', "help",   "",   "Produce this help output");
  argp.add_option('d', "datadir", "DATADIR", "Set the path to search for gamedata");

  argp.add_group("Display Options:");
  argp.add_option('g', "geometry",   "WIDTHxHEIGHT", "Set screen size");
  argp.add_option('w', "fullscreen", "",    "Switch to Fullscreen on startup");
  argp.add_option('f', "fps",        "FPS", "Limit of frames per second");

  argp.add_group("Audio Options:");
  argp.add_option('m', "music", "",  "Enable music");
  argp.add_option('s', "sound", "",  "Enable sound");

  argp.add_group("Input Options:");
  argp.add_option('c', "controller", "FILE",   "Use controller as defined in FILE");

  argp.add_group("Demo Recording/Playback Options:");
  argp.add_option('r', "record",      "FILE", "Record input events to FILE");
  argp.add_option('a', "record-video","DIR",  "Record a gameplay video to DIR");
  argp.add_option('p', "play",        "FILE", "Playback input events from FILE");

  argp.parse_args(argc, argv);

  while (argp.next())
    {
      switch(argp.get_key())
        {
        case CL_CommandLine::REST_ARG:
          mission_file = argp.get_argument();
          break;

        case 'a':
          video_record_directory = argp.get_argument();
          break;

        case 'r':
          event_record_file = argp.get_argument();
          break;

        case 'h':
          argp.print_help();
          exit(EXIT_SUCCESS);
          break;

        case 'p':
          playback_file = argp.get_argument();
          break;

        case 'f':
          fps = strtof(argp.get_argument().c_str(), 0);
          break;

        case 'V':
          std::cout << "Feuerkraft 0.1.0" << std::endl;
          exit(EXIT_SUCCESS);
          break;

        case 'v':
          verbose = true;
          break;

        case 'd':
          datadir = argp.get_argument();
          break;

        case 'q':
          verbose = false;
          break;

        case 'm':
          music_enabled = true;
          break;

        case 'c':
          controller_file = argp.get_argument();
          break;

        case 's':
          sound_enabled = true;
          break;

        case 'w':
          fullscreen = true;
          break;

        case 'g':
          if (sscanf(argp.get_argument().c_str(), "%dx%d", &screen_width, &screen_height) != 2)
            {
              std::cout << "Screen size value incorrect: '" << argp.get_argument() << "'" << std::endl;
              exit(EXIT_FAILURE);
            }
          break;

        default:
          std::cout << "CommandLineArguments: Unhandled key: " << argp.get_key() << std::endl;
          break;
        }
    }
}

/* EOF */
