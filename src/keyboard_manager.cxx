//  $Id: keyboard_manager.cxx,v 1.4 2003/10/31 23:24:41 grumbel Exp $
//
//  Feuerkraft - A Tank Battle Game
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
#include <ClanLib/Display/mouse.h>
#include "keyboard_manager.hxx"

KeyboardManager* KeyboardManager::instance_ = 0;

KeyboardManager::KeyboardManager()
{
  slots.push_back(CL_Keyboard::sig_key_down().connect(this, &KeyboardManager::button_down));
  slots.push_back(CL_Keyboard::sig_key_up().connect(this, &KeyboardManager::button_up));
  slots.push_back(CL_Mouse::sig_key_down().connect(this, &KeyboardManager::button_down));
  slots.push_back(CL_Mouse::sig_key_up().connect(this, &KeyboardManager::button_up));

  CL_InputDevice joy = CL_Joystick::get_device(1);

  slots.push_back(joy.sig_key_up().connect(this, &KeyboardManager::button_up));
  slots.push_back(joy.sig_key_down().connect(this, &KeyboardManager::button_down));
}

KeyboardManager::~KeyboardManager()
{
  for(Callbacks::iterator i = callbacks.begin(); i != callbacks.end(); ++i)
    {
      delete *i;
    }
}

void
KeyboardManager::button_up(const CL_InputEvent& event)
{
}

void
KeyboardManager::button_down(const CL_InputEvent& event)
{
  for(Callbacks::iterator i = callbacks.begin(); i != callbacks.end(); ++i)
    {
      if (event.device.get_type() != CL_InputDevice::joystick)
        {
          if (event.id == (*i)->key_id)
            {
              (*i)->run();
            }
        }
      else
        {
          if (event.id == (*i)->key_id - 1000)
            {
              (*i)->run();
            }
        }
    }
}

/* EOF */
