//  $Id$
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
#include "input_manager_custom.hxx"

InputAxis::InputAxis(CL_InputDevice& dev, int num)
  : dev(dev), axis_num(num)
{
  slots.push_back(dev.sig_axis_move().connect(this, &InputAxis::on_axis_move));
}

void
InputAxis::on_axis_move(const CL_InputEvent& event)
{
  if (event.id == axis_num)
    {
      move(event.axis_pos);
    }
}

InputButton::InputButton(CL_InputDevice& dev_, int keycode_)
  : dev(dev_), keycode(keycode_)
{
  slots.push_back(dev.sig_key_down().connect(this, &InputButton::on_key_down));
  slots.push_back(dev.sig_key_up().connect(this, &InputButton::on_key_up));
}

void
InputButton::on_key_down(const CL_InputEvent& event)
{
  if (keycode == event.id)
    {
      button_down();
    }
}

void
InputButton::on_key_up(const CL_InputEvent& event)
{
  if (keycode == event.id)
    {
      button_up();
    }
}

InputManagerCustom::InputManagerCustom()
{
  if (0)
    {
      primary_button   = new InputButton(CL_Keyboard::get_device(), CL_KEY_E);
      secondary_button = new InputButton(CL_Keyboard::get_device(), CL_KEY_P);
      use_button       = new InputButton(CL_Keyboard::get_device(), CL_KEY_K);
      menu_button      = new InputButton(CL_Keyboard::get_device(), CL_KEY_A);
    }
  else
    {
      primary_button   = new InputButton(CL_Joystick::get_device(1), 9);
      secondary_button = new InputButton(CL_Joystick::get_device(1), 8);
      use_button       = new InputButton(CL_Joystick::get_device(1), 3);
      menu_button      = new InputButton(CL_Joystick::get_device(1), 2);

      orientation_axis = new InputAxis(CL_Joystick::get_device(1), 0);
      accelerate_axis  = new InputAxis(CL_Joystick::get_device(1), 1);
      strafe_axis      = new InputAxis(CL_Joystick::get_device(1), 2);
    }

  slots.push_back(primary_button->on_key_down().connect  (this, &InputManagerCustom::on_button_down, PRIMARY_FIRE_BUTTON));
  slots.push_back(secondary_button->on_key_down().connect(this, &InputManagerCustom::on_button_down, SECONDARY_FIRE_BUTTON));
  slots.push_back(use_button->on_key_down().connect      (this, &InputManagerCustom::on_button_down, USE_BUTTON));

  slots.push_back(primary_button->on_key_up().connect  (this, &InputManagerCustom::on_button_up, PRIMARY_FIRE_BUTTON));
  slots.push_back(secondary_button->on_key_up().connect(this, &InputManagerCustom::on_button_up, SECONDARY_FIRE_BUTTON));
  slots.push_back(use_button->on_key_up().connect      (this, &InputManagerCustom::on_button_up, USE_BUTTON));
  
  slots.push_back(orientation_axis->on_move().connect(this, &InputManagerCustom::on_axis_move, ORIENTATION_AXIS));
  slots.push_back(accelerate_axis->on_move().connect(this, &InputManagerCustom::on_axis_move, ACCELERATE_AXIS));
  slots.push_back(strafe_axis->on_move().connect(this, &InputManagerCustom::on_axis_move, STRAFE_AXIS));
}

void
InputManagerCustom::on_axis_move(float pos, AxisName name)
{
  add_axis_event(name, pos);
  controller.set_axis_state(name, pos);
}

void
InputManagerCustom::on_button_up(ButtonName name)
{
  add_button_event(name, false);
  controller.set_button_state(name, false);
}

void
InputManagerCustom::on_button_down(ButtonName name)
{
  add_button_event(name, true);
  controller.set_button_state(name, true);
}

void
InputManagerCustom::update(float delta)
{
}

/* EOF */
