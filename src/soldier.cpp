// Feuerkraft - A Tank Battle Game
// Copyright (C) 2000 Ingo Ruhnke <grumbel@gmx.de>
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

#include "buildings/building_map.hpp"
#include "alist.hpp"
#include "math.hpp"
#include "view.hpp"
#include "input/controller.hpp"
#include "property_set.hpp"
#include "ai_manager.hpp"
#include "soldier.hpp"

Soldier::Soldier(const AList& lst) :
  ai(0),
  sur(resources->get_sprite("feuerkraft/soldier")),
  sur_light(resources->get_sprite("feuerkraft/soldier-light")),
  acceleration(),
  steering()
{
  pos.x = lst.get_float("x-pos");
  pos.y = lst.get_float("y-pos");
}

Soldier::~Soldier ()
{
  delete ai;
}

void
Soldier::update_controlls(const Controller& controller)
{
  acceleration = controller.get_axis_state(ACCELERATE_AXIS);
  steering     = controller.get_axis_state(ORIENTATION_AXIS);
}

void
Soldier::draw (View& view)
{
  FloatVector2d velocity;

  velocity.x = steering;
  velocity.y = acceleration;

  float new_orientation = velocity.get_orientation() + Math::pi_2;

  if (velocity.x == 0 && velocity.y == 0)
    {
      new_orientation = orientation;
      sur.set_frame(1);
    }

  sur.set_angle(Math::rad2deg(new_orientation));
  view.get_sc().color().draw(sur, pos.x, pos.y);
  view.get_sc().light().draw(sur_light, pos.x, pos.y);
  orientation = new_orientation;
}

void
Soldier::update(float delta)
{
  sur.update(delta);

  FloatVector2d velocity;

  velocity.x = steering;
  velocity.y = acceleration;

  FloatVector2d new_pos = pos + (velocity * 100.0f * delta);

  BuildingMap* building_map = GameWorld::current()->get_buildingmap();

  if (building_map->get_building(new_pos) == 0)
    {
      pos = new_pos;
    }
  else
    {
      // Soldier is stuck in a building, allow him to walk so he
      // can unstuck himself
      if (building_map->get_building(pos) != 0)
        pos = new_pos;
      else if (building_map->get_building(FloatVector2d(pos.x, new_pos.y)) == 0)
        pos = FloatVector2d(pos.x, new_pos.y);
      else if (building_map->get_building(FloatVector2d(new_pos.x, pos.y)) == 0)
        pos = FloatVector2d(new_pos.x, pos.y);
    }
}

bool
Soldier::is_colliding(FloatVector2d obj_pos)
{
  FloatVector2d diff = obj_pos - pos;
  if (diff.get_length() > 5)
    return false;
  else
    return true;
}

void
Soldier::attach_ai()
{
  if (ai == 0)
    {
      ai = new SoldierAI(this);
      AIManager::instance()->add(ai);
    }
}

void
Soldier::deattach_ai()
{
  if (ai)
    {
      AIManager::instance()->remove(ai);
      delete ai;
      ai = 0;
    }
}

/* EOF */
