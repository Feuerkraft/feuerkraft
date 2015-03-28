//  $Id$
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

#include <iostream>
#include <ClanLib/Display/input_event.h>
#include "input_button_input_device.hpp"

InputButtonInputDevice::InputButtonInputDevice(CL_InputDevice& dev_, int keycode_)
  : dev(dev_), keycode(keycode_)
{
  slots.push_back(dev.sig_key_down().connect(this, &InputButtonInputDevice::on_key_down));
  slots.push_back(dev.sig_key_up().connect(this, &InputButtonInputDevice::on_key_up));
}

void
InputButtonInputDevice::on_key_down(const CL_InputEvent& event)
{
  if (keycode == event.id)
    {
      button_down();
    }
}

void
InputButtonInputDevice::on_key_up(const CL_InputEvent& event)
{
  if (keycode == event.id)
    {
      button_up();
    }
}

/* EOF */
