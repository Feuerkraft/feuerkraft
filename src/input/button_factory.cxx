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

#include <ClanLib/Display/joystick.h>
#include <ClanLib/Display/keyboard.h>
#include "../guile.hxx"
#include "input_button.hxx"
#include "input_button_input_device.hxx"
#include "button_factory.hxx"

InputButton* 
ButtonFactory::create(SCM lst)
{
  SCM sym = gh_car(lst);

  if (gh_equal_p(sym, gh_symbol2scm("joystick-button")))
    {
      return create_joystick_button(gh_cdr(lst));
    }
  else if (gh_equal_p(sym, gh_symbol2scm("keyboard-button")))
    {
      return create_joystick_button(gh_cdr(lst));
    }
  else
    {
      std::cout << "ButtonFactory::create: parse error: ";
      gh_display(lst); std::cout << std::endl;
    }
      
  return 0;
}

InputButton*
ButtonFactory::create_joystick_button(SCM lst)
{
  int device_num = gh_scm2int(gh_car(lst));
  int button_num = gh_scm2int(gh_cadr(lst));
  
  if (device_num >= 0 && device_num < CL_Joystick::get_device_count())
    return new InputButtonInputDevice(CL_Joystick::get_device(device_num), button_num);
  else
    {
      std::cout << "Error: ButtonFactory::create_joystick_button(SCM lst)" << std::endl;
      return 0;
    }
}

InputButton*
ButtonFactory::create_keyboard_button(SCM lst)
{
  std::string key_str = Guile::symbol2string(gh_cadr(lst));
  int key_num = CL_Keyboard::get_device().keyid_to_string(key_str);
  // FIXME: No error checking
  return new InputButtonInputDevice(CL_Keyboard::get_device(), key_num);
}

/* EOF */
