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
#include "../assert.hxx"
#include "input_button_input_device.hxx"
#include "input_axis_input_device.hxx"
#include "button_factory.hxx"
#include "axis_factory.hxx"
#include "controller_def.hxx"

#include "input_manager_custom.hxx"

InputManagerCustom::InputManagerCustom(SCM lst)
{
  init(lst);

  for (int i = 0; i < (int)buttons.size(); ++i)
    {
      if (buttons[i])
        {
          slots.push_back(buttons[i]->on_key_down().connect(this, &InputManagerCustom::on_button_down, i));
          slots.push_back(buttons[i]->on_key_up().connect  (this, &InputManagerCustom::on_button_up,   i));
        }
      else
        {
          std::cout << "Button " << i << " not configured" << std::endl;
        }
    }

  for (int i = 0; i < (int)buttons.size(); ++i)
    {
      if (axes[i])
        {
          slots.push_back(axes[i]->on_move().connect(this, &InputManagerCustom::on_axis_move, i));
        }
      else
        {
          std::cout << "Axis " << i << " not configured" << std::endl;
        }
    }
}

void 
InputManagerCustom::init(SCM lst)
{
  buttons.resize(ControllerDef::get_button_count());
  axes.resize(ControllerDef::get_axis_count());
  
  std::cout << "InputManagerCustom::init" << std::endl;
  while (gh_pair_p(lst))
    {
      //gh_display(gh_car(lst)); gh_newline();
      SCM sym  = gh_caar(lst);
      SCM data = gh_cadar(lst);

      //gh_display(sym); gh_newline();
      
      std::string name = Guile::symbol2string(sym);

      int id = ControllerDef::button_name2id(name);
      if (id != -1)
        {
          buttons[id] = ButtonFactory::create(data);
        }
      else
        {
          id = ControllerDef::axis_name2id(name);
          if (id != -1)
            {
              axes[id] = AxisFactory::create(data);
            }
          else
            {
              std::cout << "InputManagerCustom::init: Error unknown tag: " << Guile::symbol2string(sym) << std::endl;
            }
        }

      lst = gh_cdr(lst);
    }
}  

void
InputManagerCustom::on_axis_move(float pos, int name)
{
  add_axis_event(name, pos);
  controller.set_axis_state(name, pos);
}

void
InputManagerCustom::on_button_up(int name)
{
  add_button_event(name, false);
  controller.set_button_state(name, false);
}

void
InputManagerCustom::on_button_down(int name)
{
  add_button_event(name, true);
  controller.set_button_state(name, true);
}

void
InputManagerCustom::update(float delta)
{
  for (int i = 0; i < (int)buttons.size(); ++i)
    {
      if (buttons[i])
        buttons[i]->update(delta);
    }

  for (int i = 0; i < (int)axes.size(); ++i)
    {
      if (axes[i])
        axes[i]->update(delta);
    }
}

/* EOF */
