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
#include <ClanLib/Display/keyboard.h>
#include <ClanLib/Display/joystick.h>
#include <ClanLib/Display/display_iostream.h>
#include <ClanLib/Display/keys.h>
#include <ClanLib/Display/input_event.h>
#include "input_manager_clanlib.hxx"

InputManagerClanLib::InputManagerClanLib()
{
  slots.connect(CL_Keyboard::sig_key_down(), this, &InputManagerClanLib::on_key_event);
  slots.connect(CL_Keyboard::sig_key_up(),   this, &InputManagerClanLib::on_key_event);

  CL_InputDevice dev = CL_Joystick::get_device(1);
  slots.connect(dev.sig_axis_move(),this, &InputManagerClanLib::on_axis_move);
  slots.connect(dev.sig_key_down(), this, &InputManagerClanLib::on_button_down);
  slots.connect(dev.sig_key_up(),   this, &InputManagerClanLib::on_button_up);
}

InputManagerClanLib::~InputManagerClanLib()
{
}

void
InputManagerClanLib::on_axis_move(const CL_InputEvent& event)
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
InputManagerClanLib::on_button_down(const CL_InputEvent& event)
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
InputManagerClanLib::on_button_up(const CL_InputEvent& event)
{
}

void
InputManagerClanLib::on_key_event(const CL_InputEvent& event)
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

        case CL_KEY_O:
          add_axis_event(STRAFE_AXIS, -1.0f);
          break;
        case CL_KEY_U:
          add_axis_event(STRAFE_AXIS, 1.0f);
          break;

        case CL_KEY_E:
          add_button_event(PRIMARY_FIRE_BUTTON, true);
          break;
        default:
          std::cout << "Unknown keypress: " << event << std::endl;
          break;
        }
      break;

    default:
      break;
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
#if 0
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

  if (CL_Keyboard::get_keycode(CL_KEY_O) && !CL_Keyboard::get_keycode(CL_KEY_U))
    controller.set_axis_state(STRAFE_AXIS, -1.0f);
  else if (CL_Keyboard::get_keycode(CL_KEY_U) && !CL_Keyboard::get_keycode(CL_KEY_O))
    controller.set_axis_state(STRAFE_AXIS, 1.0f);
  else
    controller.set_axis_state(STRAFE_AXIS, 0.0f);

  controller.set_button_state(PRIMARY_FIRE_BUTTON, 
                              CL_Keyboard::get_keycode(CL_KEY_E));
#endif 

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
