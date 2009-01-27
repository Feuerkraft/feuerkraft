//  $Id: tower_ai.cpp,v 1.1 2003/06/18 13:04:21 grumbel Exp $
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

#include "../math.hpp"
#include "../player.hpp"
#include "../unit.hpp"
#include "../property_set.hpp"
#include "tower_ai.hpp"

extern Player*  player;

TowerAI::TowerAI(Tower* arg_tower)
  : tower(arg_tower),
    ai_count(0)
{
}

void
TowerAI::update(float delta)
{
  ai_count -= delta;

  if (ai_count <= 0)
    {
      ai_count = 0.0f;

      FloatVector2d pos(tower->get_x_pos() * 40 + 40,
                        tower->get_y_pos() * 40 + 40);

      FloatVector2d target_pos = player->get_current_unit()->get_pos();
      
      FloatVector2d diff = target_pos - pos;
      
      //      float angle = Math::normalize_angle(tower->get_orientation() - diff.get_orientation());
      
      tower->Building::get_properties()->set_float("orientation", diff.get_orientation() + Math::pi);

      /*if (angle > 0)        controller.set_axis_state(ORIENTATION_AXIS, -1.0f);
      else
        controller.set_axis_state(ORIENTATION_AXIS, 1.0f);

      tower->update_controlls(controller);
      */
    }
}

GameObj*
TowerAI::get_object()
{
  return 0;
}

/* EOF */
