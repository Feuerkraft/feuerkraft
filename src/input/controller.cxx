//  $Id: controller.cxx,v 1.1 2003/06/06 18:18:13 grumbel Exp $
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

#include "../assert.hxx"
#include "controller.hxx"

Controller::Controller()
{
  orientation_axis = 0.0f;
  accelerate_axis  = 0.0f;
  
  primary_fire_button = false;
}

float
Controller::get_axis_state(AxisName name) const
{
  switch(name)
    {
    case ORIENTATION_AXIS:
      return orientation_axis;
    case ACCELERATE_AXIS:
      return accelerate_axis;
    default:
      AssertMsg(0, "Controllor: Unknown AxisName");
    }
}

bool
Controller::get_button_state(ButtonName name) const
{
  switch(name)
    {
    case PRIMARY_FIRE_BUTTON:
      return primary_fire_button;
    default:
      AssertMsg(0, "Controller: Unknown ButtonName");
    }
}

void
Controller::set_axis_state(AxisName name, float pos)
{
  switch(name)
    {
    case ORIENTATION_AXIS:
      orientation_axis = pos;
      break;
    case ACCELERATE_AXIS:
      accelerate_axis = pos;
      break;
    default:
      AssertMsg(0, "Controllor: Unknown AxisName");
    }
}

void
Controller::set_button_state(ButtonName name, bool down)
{
  switch(name)
    {
    case PRIMARY_FIRE_BUTTON:
      primary_fire_button = down;
      break;
    default:
      AssertMsg(0, "Controller: Unknown ButtonName");
    }  
}

InputEventLst
Controller::get_events() const
{
  return events;
}

/* EOF */
