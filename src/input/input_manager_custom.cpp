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
#include <ClanLib/Display/keyboard.h>
#include <ClanLib/Display/joystick.h>
#include <ClanLib/Display/display_iostream.h>
#include <ClanLib/Display/keys.h>

#include "../guile.hpp"
#include "../assert.hpp"
#include "../controller_def.hpp"
#include "input_button_input_device.hpp"
#include "input_axis_input_device.hpp"
#include "button_factory.hpp"
#include "axis_factory.hpp"

#include "input_manager_custom.hpp"

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
          std::cout << "# Warrning: Button '" << ControllerDef::button_id2name(i)
                    << "' not configured and will not be usable" << std::endl;
        }
    }

  for (int i = 0; i < (int)axes.size(); ++i)
    {
      if (axes[i])
        {
          slots.push_back(axes[i]->on_move().connect(this, &InputManagerCustom::on_axis_move, i));
        }
      else
        {
          std::cout << "# Warrning: Axis '" << ControllerDef::axis_id2name(i)
                    << "' not configured and will not be usable" << std::endl;
        }
    }
}

void 
InputManagerCustom::init(SCM lst)
{
  buttons.resize(ControllerDef::get_button_count());
  axes.resize(ControllerDef::get_axis_count());
  
  while (gh_pair_p(lst))
    {
      SCM sym  = gh_caar(lst);
      SCM data = gh_cadar(lst);

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
              std::cout << "# Warning: InputManagerCustom::init: Error unknown tag: " 
                        << Guile::scm2string(sym) << std::endl;
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
