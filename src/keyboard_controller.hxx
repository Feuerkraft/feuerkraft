//  $Id: keyboard_controller.hxx,v 1.3 2003/05/02 14:28:26 grumbel Exp $
// 
//  Pingus - A free Lemmings clone
//  Copyright (C) 2000 Ingo Ruhnke <grumbel@gmx.de>
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

#ifndef KEYBOARDCONTROLLER_HH
#define KEYBOARDCONTROLLER_HH

#include <ClanLib/Display/input_event.h>
#include <ClanLib/Display/display_window.h>
#include "controller.hxx"

class KeyboardController : public Controller
{
private:
  bool left_key;
  bool right_key;
  bool left2_key;
  bool right2_key;
  bool mine_key;
  bool fire_key;
  bool up_key;
  bool down_key;

  CL_Slot key_up_slot;
  CL_Slot key_down_slot;

  void input_down(const CL_InputEvent& key);
public:
  KeyboardController(CL_DisplayWindow* window, Controllable* obj);
  
  void update (float delta);
};

#endif

/* EOF */
