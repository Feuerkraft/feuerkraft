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

#include <ClanLib/Display/input_event.h>
#include "input_axis_input_device.hpp"

InputAxisInputDevice::InputAxisInputDevice(CL_InputDevice& dev, int num)
  : dev(dev), axis_num(num)
{
  slots.push_back(dev.sig_axis_move().connect(this, &InputAxisInputDevice::on_axis_move));
}

void
InputAxisInputDevice::on_axis_move(const CL_InputEvent& event)
{
  if (event.id == axis_num)
    {
      move(event.axis_pos);
    }
}

/* EOF */
