// Feuerkraft - A Tank Battle Game
// Copyright (C) 2002 Ingo Ruhnke <grumbel@gmx.de>
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

#ifndef HEADER_INPUT_MANAGER_IMPL_HXX
#define HEADER_INPUT_MANAGER_IMPL_HXX

#include "controller.hpp"
#include "input_event.hpp"

/** */
class InputManagerImpl
{
protected:
  Controller controller;
  InputEventLst events;

public:
  InputManagerImpl() {}
  virtual ~InputManagerImpl() {}

  virtual void update(float delta) =0;

  InputEventLst get_events();

  Controller get_controller();
  void clear();

  void add_axis_event  (int name, float pos);
  void add_button_event(int name, bool down);
private:
  InputManagerImpl(const InputManagerImpl&);
  InputManagerImpl& operator=(const InputManagerImpl&);
};

#endif

/* EOF */
