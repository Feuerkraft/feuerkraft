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
#include <ClanLib/Display/joystick.h>
#include "input_axis_input_device.hxx"
#include "axis_factory.hxx"

InputAxis* 
AxisFactory::create(SCM lst)
{
  while(gh_pair_p(lst))
    {
      SCM sym  = gh_caar(lst);
      SCM data = gh_cdar(lst);
      
      if (gh_equal_p(sym, gh_symbol2scm("joystick-axis")))
        {
          return create_joystick_axis(data);
        }
      else
        {
          std::cout << "AxisFactory::create: parse error" << std::endl;
        }

      lst = gh_cdr(lst);
    }
  return 0;
}

InputAxis*
AxisFactory::create_joystick_axis(SCM lst)
{
  int device_num = gh_scm2int(gh_car(lst));
  int axis_num   = gh_scm2int(gh_cadr(lst));

  if (device_num >= 0 && device_num < CL_Joystick::get_device_count())
    return new InputAxisInputDevice(CL_Joystick::get_device(device_num), axis_num);
  else
    {
      std::cout << "Error: AxisFactory::create_joystick_axis(SCM lst)" << std::endl;
      return 0;
    }
}

/* EOF */
