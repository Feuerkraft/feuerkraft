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

#include "../guile.hxx"
#include "input_button_input_device.hxx"
#include "input_axis_input_device.hxx"
#include "button_factory.hxx"
#include "axis_factory.hxx"

#include "input_manager_custom.hxx"

InputManagerCustom::InputManagerCustom(SCM lst)
{
  init(lst);

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
InputManagerCustom::init(SCM lst)
{
  while (gh_pair_p(lst))
    {
      SCM sym  = gh_caar(lst);
      SCM data = gh_cdar(lst);

      if (gh_equal_p(sym, gh_symbol2scm("primary-button")))
        {
          primary_button = ButtonFactory::create(data);
        }
      else if (gh_equal_p(sym, gh_symbol2scm("secondary-button")))
        {
          secondary_button =  ButtonFactory::create(data);
        }
      else if (gh_equal_p(sym, gh_symbol2scm("use-button")))
        {
          use_button = ButtonFactory::create(data);
        }
      else if (gh_equal_p(sym, gh_symbol2scm("menu-button")))
        {
          menu_button = ButtonFactory::create(data);
        }
      else if (gh_equal_p(sym, gh_symbol2scm("orientation-axis")))
        {
          orientation_axis = AxisFactory::create(data);
        }
      else if (gh_equal_p(sym, gh_symbol2scm("accelerate-axis")))
        {
          accelerate_axis = AxisFactory::create(data);
        }
      else if (gh_equal_p(sym, gh_symbol2scm("strafe-axis")))
        {
          strafe_axis = AxisFactory::create(data);
        }
      else
        {
          std::cout << "InputManagerCustom::init: Error unknown tag: " << Guile::symbol2string(sym) << std::endl;
        }
      
      lst = gh_cdr(lst);
    }
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
