//  $Id$
//
//  Feuerkraft - A Tank Battle Game
//  Copyright (C) 2003 Ingo Ruhnke <grumbel@gmx.de>
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

#include "../view.hxx"
#include "../resource_manager.hxx"
#include "rotor.hxx"

Rotor::Rotor(const std::string& slow_name,
             const std::string& fast_name)
{
  slow = CL_Sprite(resources->get_sprite(slow_name));
  fast = CL_Sprite(resources->get_sprite(fast_name));

  running      = false;
  orientation  = 0;
  velocity     = 0;
  max_velocity = 10.0f;
  acceleration = 1.5f;
}

void
Rotor::draw(View& view, const FloatVector2d& pos, float ori)
{
  if (velocity > 8.0f)
    {
      view.draw(fast, pos, orientation);
    }
  else
    {
      view.draw(slow, pos, orientation + ori);
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
