// Feuerkraft - A Tank Battle Game
// Copyright (C) 2002 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include <ClanLib/Display/joystick.h>
#include <ClanLib/Display/keyboard.h>
#include <ClanLib/Core/System/clanstring.h>
#include "../guile.hpp"
#include "../feuerkraft_error.hpp"
#include "input_button.hpp"
#include "input_axis.hpp"
#include "input_button_input_device.hpp"
#include "axis_factory.hpp"
#include "axis_button.hpp"
#include "multi_button.hpp"
#include "button_factory.hpp"

InputButton*
ButtonFactory::create(SCM lst)
{
  SCM sym = scm_car(lst);

  if (Guile::equal_p(sym, scm_from_utf8_symbol("joystick-button")))
  {
    return create_joystick_button(scm_cdr(lst));
  }
  else if (Guile::equal_p(sym, scm_from_utf8_symbol("keyboard-button")))
  {
    return create_keyboard_button(scm_cdr(lst));
  }
  else if (Guile::equal_p(sym, scm_from_utf8_symbol("axis-button")))
  {
    return create_axis_button(scm_cdr(lst));
  }
  else if (Guile::equal_p(sym, scm_from_utf8_symbol("multi-button")))
  {
    return create_multi_button(scm_cdr(lst));
  }
  else
  {
    throw FeuerkraftError("ButtonFactory::create: parse error: '"
                          + Guile::scm2string(lst) + "'");
  }

  return 0;
}

InputButton*
ButtonFactory::create_axis_button(SCM lst)
{
  InputAxis* axis = AxisFactory::create(scm_car(lst));
  bool top = scm_to_bool(scm_cadr(lst));

  return new AxisButton(axis, top);
}

InputButton*
ButtonFactory::create_joystick_button(SCM lst)
{
  int device_num = scm_to_int(scm_car(lst));
  int button_num = scm_to_int(scm_cadr(lst));

  if (device_num >= 0 && device_num < CL_Joystick::get_device_count())
    return new InputButtonInputDevice(CL_Joystick::get_device(device_num), button_num);
  else
    {
      throw FeuerkraftError("Error: ButtonFactory::create_joystick_button: device out of range"
                            + CL_String::to(device_num) + " " + Guile::scm2string(lst));
    }
}

InputButton*
ButtonFactory::create_keyboard_button(SCM lst)
{
  std::string key_str = Guile::scm2string(scm_car(lst));
  int key_num         = CL_Keyboard::get_device().string_to_keyid(key_str);

  // FIXME: No error checking
  return new InputButtonInputDevice(CL_Keyboard::get_device(), key_num);
}

InputButton*
ButtonFactory::create_multi_button(SCM lst)
{
  MultiButton* button = new MultiButton();

  while (!scm_is_true(scm_null_p(lst)))
    {
      button->add(create(scm_car(lst)));
      lst = scm_cdr(lst);
    }

  return button;
}

/* EOF */
