//  $Id$
// 
//  Pingus - A free Lemmings clone
//  Copyright (C) 2002 Ingo Ruhnke <grumbel@gmx.de>
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//  
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//  
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.

#ifndef HEADER_BUTTON_AXIS_HXX
#define HEADER_BUTTON_AXIS_HXX

#include "input_axis.hpp"

class InputButton;

class ButtonAxis : public InputAxis
{
private:
  InputButton* left;
  InputButton* right;

  bool left_state;
  bool right_state;
  
  float pos;
private:
  void on_left_up();
  void on_left_down();

  void on_right_up();
  void on_right_down();
public:
  ButtonAxis(InputButton* left, InputButton* right);
  void update(float delta);
};

#endif

/* EOF */
