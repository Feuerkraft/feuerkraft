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

#ifndef HEADER_INPUT_MANAGER_HXX
#define HEADER_INPUT_MANAGER_HXX

#include <vector>
#include "controller.hpp"
#include "input_event.hpp"

class InputRecorder;
class InputManagerImpl;

/** */
class InputManager
{
private:
  static InputManagerImpl* impl;
  static InputRecorder* recorder;
public:
  /** Init the InputManager with the data found in \a filename */
  static void init(const std::string& filename = std::string());

  /** Init the playback of a previously recorded file */
  static void init_playback(const std::string& filenam);
  static void deinit();

  /** Record all input events to \a filename */
  static void setup_recorder(const std::string& filename);

  static void update(float delta);
  static Controller get_controller();
  static void clear();
private:
  InputManager(const InputManager&);
  InputManager& operator=(const InputManager&);
};

#endif

/* EOF */
