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

#include "../game_world.hpp"
#include "../math.hpp"
#include "fire_particle.hpp"
#include "smoke_particle.hpp"
#include "smoke_emitter.hpp"

SmokeEmitter::SmokeEmitter(const FloatVector2d& arg_pos)
  : pos(arg_pos)
{
  last_particle = 0.0f;
}

void
SmokeEmitter::set_pos(const FloatVector2d& arg_pos)
{
  pos = arg_pos;
}

void
SmokeEmitter::update(float delta)
{
  float particle_release_count = .3f;

  last_particle += delta;

  GameWorld::current()->add(new FireParticle(pos+ FloatVector2d::make_polar(Math::frand() * 5,
                                                                                  Math::frand() * Math::pi*2)));

  while (last_particle > particle_release_count)
    {
      GameWorld::current()->add(new FireParticle(pos + FloatVector2d::make_polar(Math::frand() * 5,
                                                                                  Math::frand() * Math::pi*2)));

      GameWorld::current()->add(new SmokeParticle(pos + FloatVector2d::make_polar(Math::frand() * 20,
                                                                                  Math::frand() * Math::pi*2)));
      last_particle -= particle_release_count;
    }
}

/* EOF */
