//  $Id: input_manager_clanlib.hxx,v 1.5 2003/10/31 23:24:41 grumbel Exp $
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

#ifndef HEADER_INPUT_MANAGER_CLANLIB_HXX
#define HEADER_INPUT_MANAGER_CLANLIB_HXX

#include <ClanLib/Signals/slot.h>
#include <ClanLib/Signals/slot_container.h>
#include "controller.hxx"
#include "input_manager_impl.hxx"

class CL_InputEvent;

/** */
class InputManagerClanLib : public InputManagerImpl
{
private:
  Controller controller;
  InputEventLst events;

  CL_SlotContainer slots;
  
  void on_key_event(const CL_InputEvent& event);
  void on_axis_move(const CL_InputEvent& event);
  void on_button_down(const CL_InputEvent& event);
  void on_button_up(const CL_InputEvent& event);

  void add_axis_event(AxisName name, float pos);
  void add_button_event(ButtonName name, bool down);
public:
  InputManagerClanLib();
  virtual ~InputManagerClanLib();

  void update(float delta);
  InputEventLst get_events();
  Controller get_controller();
  void clear();
private:
  InputManagerClanLib (const InputManagerClanLib&);
  InputManagerClanLib& operator= (const InputManagerClanLib&);
};

#endif

/* EOF */
