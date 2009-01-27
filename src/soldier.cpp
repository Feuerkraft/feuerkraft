//  $Id: soldier.cxx,v 1.18 2003/06/20 20:54:23 grumbel Exp $
//
//  Feuerkraft - A Tank Battle Game
//  Copyright (C) 2000 Ingo Ruhnke <grumbel@gmx.de>
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

#include "buildings/building_map.hxx"
#include "alist.hxx"
#include "math.hxx"
#include "view.hxx"
#include "input/controller.hxx"
#include "property_set.hxx"
#include "ai_manager.hxx"
#include "soldier.hxx"

Soldier::Soldier(const AList& lst) 
  : ai(0),
    sur(resources->get_sprite("feuerkraft/soldier")),
    sur_light(resources->get_sprite("feuerkraft/soldier-light"))
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
