//  $Id: input_manager.cxx,v 1.4 2003/08/20 00:15:10 grumbel Exp $
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

#include <assert.h>
#include <iostream>
#include <stdexcept>
#include <sstream>
#include <ClanLib/Display/joystick.h>
#include "../command_line_arguments.hxx"
#include "input_manager_joystick.hxx"
#include "input_manager_keyboard.hxx"
#include "input_manager_custom.hxx"
#include "input_manager_impl.hxx"
#include "input_manager.hxx"

extern CommandLineArguments* args;
InputManagerImpl* InputManager::impl = 0;

void
InputManager::init(InputManagerImpl* arg_impl)
{
  if (impl)
    {
      delete impl;
      impl = 0;
    }

  if (arg_impl)
    { 
      impl = arg_impl;
    }
  else
    {
      impl = new InputManagerCustom
        (gh_eval_str("'("
                     "(primary-button   (joystick-button 1 1))"
                     "(secondary-button (joystick-button 1 2))"
                     "(use-button       (joystick-button 1 3))"
                     "(menu-button      (joystick-button 1 4))"
                     "(orientation-axis (joystick-axis 1 2))"
                     "(accelerate-axis  (joystick-axis 1 3))"
                     "(strafe-axis      (joystick-axis 1 0))"
                     ")"));
    }
  /*
  else if (args->joystick != -1)
    {
      if (args->joystick < CL_Joystick::get_device_count())
        {
          std::cout << "InputManager: Using joystick " << args->joystick << std::endl;
          impl = new InputManagerJoystick();
        }
      else
        {
          std::ostringstream os;
          os << "Feuerkraft: ClanLib doesn't have joystick number " << args->joystick
             << ", only " << CL_Joystick::get_device_count() << " joysticks available" << std::endl;
          throw std::runtime_error(os.str());
        }
    }
  else 
    {
      std::cout << "InputManager: Using keyboard" << std::endl;
      impl = new InputManagerKeyboard();
    }
  */
}

void 
InputManager::deinit()
{
  delete impl;
}

void
InputManager::update(float delta)
{
  assert(impl);
  impl->update(delta);
}

InputEventLst
InputManager::get_events()
{
  assert(impl);
  return impl->get_events();
}

Controller
InputManager::get_controller()
{
  assert(impl);
  return impl->get_controller();
}

void
InputManager::clear()
{
  impl->clear();
}

/* EOF */
