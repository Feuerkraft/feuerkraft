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

#ifndef HEADER_INPUT_AXIS_INPUT_DEVICE_HXX
#define HEADER_INPUT_AXIS_INPUT_DEVICE_HXX

#include <SDL.h>
#include "input_axis.hpp"

/** Joystick axis backed by SDL. For now keyboard axes are not used. */
class InputAxisInputDevice : public InputAxis
{
private:
  SDL_Joystick* joystick;
  int axis_num;
  float last_pos;

public:
  InputAxisInputDevice(SDL_Joystick* joystick, int num);
  void update(float delta) override;
};

#endif

/* EOF */
