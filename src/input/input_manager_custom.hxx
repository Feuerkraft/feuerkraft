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

#ifndef HEADER_INPUT_MANAGER_CUSTOM_HXX
#define HEADER_INPUT_MANAGER_CUSTOM_HXX

#include <ClanLib/Display/input_device.h>
#include <ClanLib/Display/input_event.h>
#include "input_event.hxx"
#include "input_manager_impl.hxx"

class InputAxis
{
private:
  CL_InputDevice dev;
  int axis_num;

  std::vector<CL_Slot> slots;
  CL_Signal_v1<float> move;  
public:
  InputAxis() {}
  InputAxis(CL_InputDevice& dev, int num);
  
  void on_axis_move(const CL_InputEvent& event); 

  void update(float delta) {}

  CL_Signal_v1<float>& on_move() { return move; }
};

class InputButton
{
private:
  CL_InputDevice dev;
  int keycode;

  std::vector<CL_Slot> slots;
  CL_Signal_v0 button_down;
  CL_Signal_v0 button_up;
public:
  InputButton() {}
  InputButton(CL_InputDevice& dev, int keycode);
  
  void on_key_down(const CL_InputEvent& event);
  void on_key_up(const CL_InputEvent& event);

  void update(float delta) {}

  CL_Signal_v0& on_key_down() { return button_down; }
  CL_Signal_v0& on_key_up()   { return button_up; }
};

/** */
class InputManagerCustom : public InputManagerImpl
{
private:
  std::vector<CL_Slot> slots;

  InputButton* primary_button;
  InputButton* secondary_button;
  InputButton* use_button;
  InputButton* menu_button;

  InputAxis* orientation_axis;
  InputAxis* accelerate_axis;
  InputAxis* strafe_axis;

public:
  InputManagerCustom();
  
  void update(float delta);

  void on_button_up(ButtonName name);
  void on_button_down(ButtonName name);
  void on_axis_move(float pos, AxisName name);
private:
  InputManagerCustom (const InputManagerCustom&);
  InputManagerCustom& operator= (const InputManagerCustom&);
};

#endif

/* EOF */
