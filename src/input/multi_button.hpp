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

#ifndef HEADER_MULTI_BUTTON_HXX
#define HEADER_MULTI_BUTTON_HXX

#include <vector>
#include "input_button.hpp"

/** */
class MultiButton : public InputButton
{
private:
  typedef std::vector<InputButton*> Buttons;
  Buttons buttons;
  std::vector<CL_Slot> slots;
  int press_count;
public:
  MultiButton();

  void add(InputButton*);
  void update(float delta);
private:
  void released();
  void pressed();
};

#endif

/* EOF */
