//  $Id$
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

#include "resource_manager.hxx"
#include "collision_manager.hxx"
#include "explosion.hxx"
#include "particles/rocket_smoke_particle.hxx"
#include "view.hxx"
#include "buildings/building.hxx"
#include "rocket.hxx"

Rocket::Rocket(const FloatVector2d& pos, float orientation)
  : pos(pos),
    orientation(orientation),
    velocity(10.0f),
    max_velocity(50.0f),
    life_time(0)
{
  release_count = 0;
  sprite = resources->get_sprite("feuerkraft/rocket");
  smoke  = resources->get_sprite("feuerkraft/rocket_smoke");
}

Rocket::~Rocket()
{
}

void
Rocket::draw(View& view)
{
  view.draw(sprite, pos, orientation);
}

void
Rocket::update(float delta)
{
  pos += FloatVector2d(velocity, 0).rotate(orientation);

  velocity += 10.0f * delta;
  if (velocity > max_velocity)
    velocity = max_velocity;

  CollisionManager::current()->add_point(get_id(), pos.x, pos.y);

  release_count += delta;
  if (release_count > 0.03f)
    GameWorld::current()->add(new RocketSmokeParticle(pos));

  while (release_count > 0.03f)
    {
      release_count -= 0.03f;
    }

  life_time += delta;
  if (life_time > 2.0f)
    {
      detonate();
    }
}

void
Rocket::on_collision_with_building(Building* building)
{
  building->collide(35);
  detonate();
}

void
Rocket::detonate()
{
  GameWorld::current()->add_front(new Explosion(pos, Explosion::MEDIUM));
  remove();
}

/* EOF */
