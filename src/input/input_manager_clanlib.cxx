//  $Id: input_manager_clanlib.cxx,v 1.3 2003/06/06 09:49:00 grumbel Exp $
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

#include <ClanLib/Display/keyboard.h>
#include <ClanLib/Display/keys.h>
#include "input_manager_clanlib.hxx"

InputManagerClanLib::InputManagerClanLib()
{
  
}

InputManagerClanLib::~InputManagerClanLib()
{
}

void
InputManagerClanLib::update(float delta)
{
  {
    InputEvent accelerate_event;
    accelerate_event.type = AXIS_EVENT;
    accelerate_event.axis.name = ACCELERATE_AXIS;
    if (CL_Keyboard::get_keycode(CL_KEY_DOWN))
      accelerate_event.axis.pos = 1.0f;
    else if (CL_Keyboard::get_keycode(CL_KEY_UP))
      accelerate_event.axis.pos = -1.0f;
    else
      accelerate_event.axis.pos = 0.0f;
    
    events.push_back(accelerate_event);
  }

  {
    InputEvent orientation_event;
    orientation_event.type = AXIS_EVENT;
    orientation_event.axis.name = ORIENTATION_AXIS;
    if (CL_Keyboard::get_keycode(CL_KEY_LEFT))
      orientation_event.axis.pos = -1.0f;
    else if (CL_Keyboard::get_keycode(CL_KEY_RIGHT))
      orientation_event.axis.pos = 1.0f;
    else
      orientation_event.axis.pos = 0.0f;
    
    events.push_back(orientation_event);
  }

  {
    InputEvent fire_event;
    fire_event.type = BUTTON_EVENT;
    fire_event.button.name = PRIMARY_FIRE_BUTTON;
    fire_event.button.down = CL_Keyboard::get_keycode(CL_KEY_O);
    events.push_back(fire_event);
  }
}

InputEventLst
InputManagerClanLib::get_events()
{
  InputEventLst old_events = events;
  events.clear();
  return old_events;
}

/* EOF */
