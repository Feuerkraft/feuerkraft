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

#include "input_axis_input_device.hpp"

InputAxisInputDevice::InputAxisInputDevice(SDL_GameController* controller_, int axis_num)
  : controller(controller_),
    axis(static_cast<SDL_GameControllerAxis>(axis_num)),
    last_pos(0.0f),
    deadzone(0.15f)
{
}

void
InputAxisInputDevice::update(float /*delta*/)
{
  if (!controller)
    return;

  Sint16 raw = SDL_GameControllerGetAxis(controller, axis);
  float pos = raw / 32767.0f;
  if (pos > 1.0f) pos = 1.0f;
  if (pos < -1.0f) pos = -1.0f;

  // Apply deadzone
  if (pos > -deadzone && pos < deadzone)
    pos = 0.0f;
  else if (pos > 0.0f)
    pos = (pos - deadzone) / (1.0f - deadzone);
  else
    pos = (pos + deadzone) / (1.0f - deadzone);

  if (pos != last_pos)
    {
      move(pos);
      last_pos = pos;
    }
}

/* EOF */
