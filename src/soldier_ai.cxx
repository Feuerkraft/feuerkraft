//  $Id: soldier_ai.cxx,v 1.2 2003/06/18 14:38:28 grumbel Exp $
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

#include <iostream>
#include "math.hxx"
#include "soldier.hxx"
#include "soldier_ai.hxx"

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
