//  $Id: input_manager_clanlib.cxx,v 1.10 2003/10/31 23:24:41 grumbel Exp $
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
#include <stdexcept>
#include <ClanLib/Display/keyboard.h>
#include <ClanLib/Display/joystick.h>
#include <ClanLib/Display/display_iostream.h>
#include <ClanLib/Display/keys.h>
#include <ClanLib/Display/input_event.h>
#include "input_manager_joystick.hxx"

InputManagerJoystick::InputManagerJoystick()
{
  if (CL_Joystick::get_device_count() == 1)
    {
      dev = CL_Joystick::get_device(0);
    }
  else if (CL_Joystick::get_device_count() >= 2)
    {
      // FIXME: Hack for localhost...
      dev = CL_Joystick::get_device(1);
    }
  else
    {
      throw std::runtime_error("Feuerkraft: No joystick found");
    }
  
  slots.connect(dev.sig_axis_move(),this, &InputManagerJoystick::on_axis_move);
  slots.connect(dev.sig_key_down(), this, &InputManagerJoystick::on_button_down);
  slots.connect(dev.sig_key_up(),   this, &InputManagerJoystick::on_button_up);
}

InputManagerJoystick::~InputManagerJoystick()
{
}

void
InputManagerJoystick::on_axis_move(const CL_InputEvent& event)
{
  //std::cout << "Axis: " << event.id << " " << event.axis_pos << std::endl;
  if (event.id == 0)
    add_axis_event(ORIENTATION_AXIS, event.axis_pos); 
  else if (event.id == 1)
    add_axis_event(ACCELERATE_AXIS, event.axis_pos); 
  else if (event.id == 2)
    add_axis_event(STRAFE_AXIS, event.axis_pos); 
}

void
InputManagerJoystick::on_button_down(const CL_InputEvent& event)
{
  switch (event.id)
    {
    case 9:
      add_button_event(PRIMARY_FIRE_BUTTON, true);
      break;
    case 8:
      add_button_event(SECONDARY_FIRE_BUTTON, true);
      break;
    case 3:
      add_button_event(USE_BUTTON, true);
      break;
    }
}

void
InputManagerJoystick::on_button_up(const CL_InputEvent& event)
{
}

void
InputManagerJoystick::add_axis_event(AxisName name, float pos)
{
  InputEvent event;
  event.type = AXIS_EVENT;
  event.axis.name = name;
  event.axis.pos  = pos;
  events.push_back(event);
}

void
InputManagerJoystick::add_button_event(ButtonName name, bool down)
{
  InputEvent event;
  event.type = BUTTON_EVENT;
  event.button.name = name;
  event.button.down = down;
  events.push_back(event);
}

void
InputManagerJoystick::update(float delta)
{
  CL_InputDevice dev = CL_Joystick::get_device(1);

  controller.set_axis_state(ORIENTATION_AXIS, dev.get_axis(0));
  controller.set_axis_state(ACCELERATE_AXIS,  dev.get_axis(1));
  controller.set_axis_state(STRAFE_AXIS,      dev.get_axis(2));

  controller.set_button_state(PRIMARY_FIRE_BUTTON, 
                              dev.get_keycode(9));
  controller.set_button_state(SECONDARY_FIRE_BUTTON, 
                              dev.get_keycode(8));
  controller.set_button_state(USE_BUTTON, 
                              dev.get_keycode(3));
}

InputEventLst
InputManagerJoystick::get_events()
{
  InputEventLst old_events = events;
  return old_events;
}

Controller
InputManagerJoystick::get_controller()
{
  controller.events = events;
  return controller;
}

void
InputManagerJoystick::clear()
{
  events.clear();
}

/* EOF */
