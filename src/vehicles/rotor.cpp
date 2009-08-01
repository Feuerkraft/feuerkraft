//  $Id$
//
//  Feuerkraft - A Tank Battle Game
//  Copyright (C) 2003 Ingo Ruhnke <grumbel@gmx.de>
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

#include "../view.hpp"
#include "../resource_manager.hpp"
#include "../math.hpp"
#include "rotor.hpp"

Rotor::Rotor(const RotorDescription& desc)
{
  // Rotor::Description
  direction = desc.direction;
  slow = CL_Sprite(resources->get_sprite(desc.slow_sprite));
  fast = CL_Sprite(resources->get_sprite(desc.fast_sprite));
  offset = desc.offset;

  running      = false;
  orientation  = 0;
  velocity     = 0;
  max_velocity = 10.0f;
  acceleration = 1.5f;
}

void
Rotor::draw(View& view, const FloatVector2d& pos, float parent_orientation)
{
  FloatVector2d off = offset;
  FloatVector2d p = pos + off.rotate(parent_orientation);

  if (velocity > 8.0f)
    {
      if (direction == RotorDescription::LEFT)
        {
          fast.set_angle(Math::rad2deg(orientation));
          view.get_sc().color().draw(fast, p.x, p.y);
        }
      else
        {
          fast.set_angle(Math::rad2deg(-orientation));
          view.get_sc().color().draw(fast, p.x, p.y);
        }
    }
  else
    {
      if (direction == RotorDescription::LEFT)
        {
          slow.set_angle(Math::rad2deg(orientation));
          view.get_sc().color().draw(slow, p.x, p.y);
        }
      else
        {
          slow.set_angle(Math::rad2deg(-orientation));
          view.get_sc().color().draw(slow, p.x, p.y);
        }
    }
}

void
Rotor::update(float delta)
{
  fast.update(delta);
  fast.set_angle(orientation);

  slow.update(delta);
  slow.set_angle(orientation);

  orientation += velocity * delta;

  if (running)
    {
      velocity += acceleration * delta;

      if (velocity > max_velocity)
        velocity = max_velocity;
    }
  else
    {
      velocity -= acceleration * delta;

      if (velocity < 0)
        velocity = 0;
    }
}

void
Rotor::start()
{
  running = true;
}

void
Rotor::stop()
{
  running = false;
}

/* EOF */
