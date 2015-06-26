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

#ifndef HEADER_FEUERKRAFT_COMMAND_LINE_ARGUMENTS_HXX
#define HEADER_FEUERKRAFT_COMMAND_LINE_ARGUMENTS_HXX

#include <string>

/** */
struct CommandLineArguments
{
public:
  int screen_width;
  int screen_height;

  /** Mission file to start, empty() if non is given */
  std::string mission_file;

  /** Path to all the datafiles */
  std::string datadir;
  std::string controller_file;

  /** File to which all input events should be logged */
  std::string event_record_file;

  /** Directory to which gameplay-video (aka screenshots) get saved */
  std::string video_record_directory;

  /** File from which recorded events will be played back */
  std::string playback_file;

  /** number of fps to which the game should limit itself */
  float fps;

  /** Number of the joystick to use, -1 for keyboard support */
  int joystick;

  bool music_enabled;
  bool sound_enabled;

  bool fullscreen;

  bool verbose;

  CommandLineArguments();
  CommandLineArguments(int argc, char** argv);

  void load_defaults();
  void parse_arguments(int argc, char** argv);
};

extern CommandLineArguments* args;

#endif

/* EOF */
