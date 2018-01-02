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
#include "input_axis_input_device.hpp"
#include "../feuerkraft_error.hpp"
#include "../guile.hpp"
#include "button_factory.hpp"
#include "button_axis.hpp"
#include "axis_factory.hpp"

InputAxis*
AxisFactory::create(SCM lst)
{
  while(scm_pair_p(lst))
    {
      SCM sym  = scm_car(lst);
      SCM data = scm_cdr(lst);

      if (scm_equal_p(sym, scm_from_utf8_symbol("joystick-axis")))
        {
          return create_joystick_axis(data);
        }
      if (scm_equal_p(sym, scm_from_utf8_symbol("button-axis")))
        {
          return create_button_axis(data);
        }
      else
        {
          throw FeuerkraftError("AxisFactory::create: parse error");
        }

      lst = scm_cdr(lst);
    }
  return 0;
}

InputAxis*
AxisFactory::create_joystick_axis(SCM lst)
{
  int device_num = scm_to_int(scm_car(lst));
  int axis_num   = scm_to_int(scm_cadr(lst));

  if (device_num >= 0 && device_num < CL_Joystick::get_device_count())
    return new InputAxisInputDevice(CL_Joystick::get_device(device_num), axis_num);
  else
    {
      throw FeuerkraftError("Error: AxisFactory::create_joystick_axis: "
                            + Guile::scm2string(lst));
      return 0;
    }
}

InputAxis*
AxisFactory::create_button_axis(SCM lst)
{
  InputButton* left  = ButtonFactory::create(scm_car(lst));
  InputButton* right = ButtonFactory::create(scm_cadr(lst));

  return new ButtonAxis(left, right);
}

/* EOF */
