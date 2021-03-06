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

#include <iostream>
#include "math.hpp"
#include "soldier.hpp"
#include "soldier_ai.hpp"

SoldierAI::SoldierAI(Soldier* arg_soldier)
  : soldier(arg_soldier),
    state(GOTO_TARGET)
{
  target_pos = FloatVector2d(2000.0f, 2000.0f);
}

void
SoldierAI::update(float delta)
{
  switch(state)
    {
    case RANDOM:
      controller.set_axis_state(ACCELERATE_AXIS,  Math::frand()*2.0f - 1.0f);
      controller.set_axis_state(ORIENTATION_AXIS, Math::frand()*2.0f - 1.0f);
      break;

    case WAITING:
      controller.set_axis_state(ACCELERATE_AXIS,  0);
      controller.set_axis_state(ORIENTATION_AXIS, 0);
      break;

    case GOTO_TARGET:
      /*std::cout << "Soldier: "
                << target_pos << " "
                << soldier->get_pos() << " "
                << (target_pos - soldier->get_pos()).get_length() << std::endl;*/

      if (target_pos.y > soldier->get_pos().y)
        controller.set_axis_state(ACCELERATE_AXIS,  1.0f);
      else if (target_pos.y < soldier->get_pos().y)
        controller.set_axis_state(ACCELERATE_AXIS,   -1.0f);

      if (target_pos.x > soldier->get_pos().x)
        controller.set_axis_state(ORIENTATION_AXIS,  1.0f);
      else if (target_pos.x < soldier->get_pos().x)
        controller.set_axis_state(ORIENTATION_AXIS,  -1.0f);

      if ((target_pos - soldier->get_pos()).get_length() < 10.0f)
        state = WAITING;

      break;

    default:
      break;
    }

  soldier->update_controlls(controller);
}

void
SoldierAI::goto_to(const FloatVector2d& arg_target_pos)
{
  state = GOTO_TARGET;
  target_pos = arg_target_pos;
}

void
SoldierAI::stop()
{
  state = WAITING;
}

GameObj*
SoldierAI::get_object()
{
  return soldier;
}

/* EOF */
