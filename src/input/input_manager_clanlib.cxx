//  $Id: input_manager_clanlib.cxx,v 1.7 2003/06/17 22:06:13 grumbel Exp $
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

#include <iostream>
#include <ClanLib/Display/keyboard.h>
#include <ClanLib/Display/keys.h>
#include <ClanLib/Display/input_event.h>
#include "input_manager_clanlib.hxx"

InputManagerClanLib::InputManagerClanLib()
{
  key_down = CL_Keyboard::sig_key_down().connect(this, &InputManagerClanLib::on_key_event);
  key_up   = CL_Keyboard::sig_key_up().connect(this, &InputManagerClanLib::on_key_event);
}

InputManagerClanLib::~InputManagerClanLib()
{
}

void
InputManagerClanLib::on_key_event(const CL_InputEvent& event)
{
  if (event.device.get_type() == CL_InputDevice::keyboard)
    {
      switch (event.type)
      {
      case CL_InputEvent::released:
        //std::cout << "Release: " << event.id << std::endl;
        break;

      case CL_InputEvent::pressed:
        //std::cout << "Press: " << event.id << std::endl;
        switch (event.id)
          {
            // Steering
          case CL_KEY_DOWN:
            add_axis_event(ACCELERATE_AXIS, 1.0f);
            break;
          case CL_KEY_UP:
            add_axis_event(ACCELERATE_AXIS, -1.0f);
            break;
          case CL_KEY_RIGHT:
            add_axis_event(ORIENTATION_AXIS, 1.0f);
            break;
          case CL_KEY_LEFT:
            add_axis_event(ORIENTATION_AXIS, -1.0f);
            break;

            // Fire buttons
          case CL_KEY_E:
            add_button_event(PRIMARY_FIRE_BUTTON, true);
            break;
          }
        break;
      }
    }
}

void
InputManagerClanLib::add_axis_event(AxisName name, float pos)
{
  InputEvent event;
  event.type = AXIS_EVENT;
  event.axis.name = name;
  event.axis.pos  = pos;
  events.push_back(event);
}

void
InputManagerClanLib::add_button_event(ButtonName name, bool down)
{
  InputEvent event;
  event.type = BUTTON_EVENT;
  event.button.name = name;
  event.button.down = down;
  events.push_back(event);
}

void
InputManagerClanLib::update(float delta)
{
  if (CL_Keyboard::get_keycode(CL_KEY_LEFT))
    {
      if (CL_Keyboard::get_keycode(CL_KEY_RIGHT))
        controller.set_axis_state(ORIENTATION_AXIS, 0);
      else
        controller.set_axis_state(ORIENTATION_AXIS, -1.0);
    }
  else if (CL_Keyboard::get_keycode(CL_KEY_RIGHT))
    {
      controller.set_axis_state(ORIENTATION_AXIS, 1.0);
    }
  else
    {
      controller.set_axis_state(ORIENTATION_AXIS, 0);
    }

  if (CL_Keyboard::get_keycode(CL_KEY_UP))
    {
      if (CL_Keyboard::get_keycode(CL_KEY_DOWN))
        controller.set_axis_state(ACCELERATE_AXIS, 0);
      else
        controller.set_axis_state(ACCELERATE_AXIS, -1.0);
    }
  else if (CL_Keyboard::get_keycode(CL_KEY_DOWN))
    {
      controller.set_axis_state(ACCELERATE_AXIS, 1.0);
    }
  else
    {
      controller.set_axis_state(ACCELERATE_AXIS, 0);
    }

  controller.set_button_state(PRIMARY_FIRE_BUTTON, 
                              CL_Keyboard::get_keycode(CL_KEY_E));

  {
    InputEvent fire_event;
    fire_event.type = BUTTON_EVENT;
    fire_event.button.name = PRIMARY_FIRE_BUTTON;
    fire_event.button.down = CL_Keyboard::get_keycode(CL_KEY_O);
    events.push_back(fire_event);
  }
}

InputEventLst
InputManagerClanLib::get_events()
{
  InputEventLst old_events = events;
  return old_events;
}

Controller
InputManagerClanLib::get_controller()
{
  controller.events = events;
  return controller;
}

void
InputManagerClanLib::clear()
{
  events.clear();
}

/* EOF */
