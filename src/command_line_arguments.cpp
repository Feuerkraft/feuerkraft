// Feuerkraft - A Tank Battle Game
// Copyright (C) 2002 Ingo Ruhnke <grumbel@gmail.com>
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
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <string>

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
  screen_width  = 800;
  screen_height = 600;
  scale         = 1;
  fullscreen    = false;

  mission_file = "";
  fps          = 30.0f;
  joystick     = -1;
  verbose      = true;
  datadir      = "";
  music_enabled = false;
  sound_enabled = false;
}

static void
print_help(const char* argv0)
{
  std::cout
    << "Usage: " << argv0 << " [LEVELFILE] [OPTIONS]\n"
    << "Feuerkraft is a tank battle game\n\n"
    << "General Options:\n"
    << "  -v, --verbose              Produce verbose output\n"
    << "  -V, --version              Print the exact version of the game\n"
    << "  -q, --quiet                Produce no output\n"
    << "  -h, --help                 Produce this help output\n"
    << "  -d, --datadir DATADIR      Set the path to search for gamedata\n\n"
    << "Display Options:\n"
    << "  -g, --geometry WIDTHxHEIGHT  Set window size in pixels\n"
    << "      --size WIDTHxHEIGHT      Alias for --geometry\n"
    << "      --scale FACTOR           Pixel scale (default 1). Logical\n"
    << "                               resolution becomes size/scale; e.g.\n"
    << "                               --size 1280x960 --scale 2 matches\n"
    << "                               --size 640x480 --scale 1\n"
    << "  -w, --fullscreen           Switch to Fullscreen on startup\n"
    << "  -f, --fps FPS              Limit of frames per second\n\n"
    << "Audio Options:\n"
    << "  -m, --music                Enable music\n"
    << "  -s, --sound                Enable sound\n\n"
    << "Input Options:\n"
    << "  -c, --controller FILE      Use controller as defined in FILE\n\n"
    << "Demo Recording/Playback Options:\n"
    << "  -r, --record FILE          Record input events to FILE\n"
    << "  -a, --record-video DIR     Record a gameplay video to DIR\n"
    << "  -p, --play FILE            Playback input events from FILE\n";
}

void
CommandLineArguments::parse_arguments(int argc, char** argv)
{
  for (int i = 1; i < argc; ++i)
    {
      const char* arg = argv[i];
      auto need_arg = [&](const char* name) -> const char* {
        if (i + 1 >= argc)
          {
            std::cerr << "Option " << name << " requires an argument\n";
            std::exit(EXIT_FAILURE);
          }
        return argv[++i];
      };

      if (arg[0] != '-')
        {
          mission_file = arg;
          continue;
        }

      std::string opt = arg;
      if (opt == "-h" || opt == "--help")
        {
          print_help(argv[0]);
          std::exit(EXIT_SUCCESS);
        }
      else if (opt == "-V" || opt == "--version")
        {
          std::cout << "Feuerkraft 0.2.0\n";
          std::exit(EXIT_SUCCESS);
        }
      else if (opt == "-v" || opt == "--verbose")
        {
          verbose = true;
        }
      else if (opt == "-q" || opt == "--quiet")
        {
          verbose = false;
        }
      else if (opt == "-d" || opt == "--datadir")
        {
          datadir = need_arg(opt.c_str());
        }
      else if (opt == "-g" || opt == "--geometry" || opt == "--size")
        {
          const char* geo = need_arg(opt.c_str());
          if (sscanf(geo, "%dx%d", &screen_width, &screen_height) != 2)
            {
              std::cerr << "Screen size value incorrect: '" << geo << "'\n";
              std::exit(EXIT_FAILURE);
            }
        }
      else if (opt == "--scale")
        {
          scale = static_cast<int>(strtol(need_arg(opt.c_str()), nullptr, 10));
          if (scale < 1)
            {
              std::cerr << "Scale must be >= 1\n";
              std::exit(EXIT_FAILURE);
            }
        }
      else if (opt == "-w" || opt == "--fullscreen")
        {
          fullscreen = true;
        }
      else if (opt == "-f" || opt == "--fps")
        {
          fps = strtof(need_arg(opt.c_str()), nullptr);
        }
      else if (opt == "-m" || opt == "--music")
        {
          music_enabled = true;
        }
      else if (opt == "-s" || opt == "--sound")
        {
          sound_enabled = true;
        }
      else if (opt == "-c" || opt == "--controller")
        {
          controller_file = need_arg(opt.c_str());
        }
      else if (opt == "-r" || opt == "--record")
        {
          event_record_file = need_arg(opt.c_str());
        }
      else if (opt == "-a" || opt == "--record-video")
        {
          video_record_directory = need_arg(opt.c_str());
        }
      else if (opt == "-p" || opt == "--play")
        {
          playback_file = need_arg(opt.c_str());
        }
      else
        {
          std::cerr << "Unknown option: " << opt << "\n";
          print_help(argv[0]);
          std::exit(EXIT_FAILURE);
        }
    }
}

/* EOF */
