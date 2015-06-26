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

#ifndef HEADER_INPUT_MANAGER_CUSTOM_HXX
#define HEADER_INPUT_MANAGER_CUSTOM_HXX

#include <guile/gh.h>
#include <ClanLib/Display/input_device.h>
#include <ClanLib/Display/input_event.h>
#include "input_event.hpp"
#include "input_button.hpp"
#include "input_axis.hpp"
#include "input_manager_impl.hpp"

/** */
class InputManagerCustom : public InputManagerImpl
{
private:
  std::vector<CL_Slot> slots;

  typedef std::vector<InputAxis*>   Axes;
  typedef std::vector<InputButton*> Buttons;

  Axes    axes;
  Buttons buttons;

public:
  InputManagerCustom(SCM lst);

  void update(float delta);

  void on_button_up(int name);
  void on_button_down(int name);
  void on_axis_move(float pos, int name);
private:
  void init(SCM lst);

  InputManagerCustom (const InputManagerCustom&);
  InputManagerCustom& operator= (const InputManagerCustom&);
};

#endif

/* EOF */
