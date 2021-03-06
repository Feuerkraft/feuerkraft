// Feuerkraft - A Tank Battle Game
// Copyright (C) 2000 Ingo Ruhnke <grumbel@gmail.com>
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

#include "shockwave.hpp"
#include "explosion.hpp"
#include "generic/random.hpp"
#include "sound/sound.hpp"
#include "particles/explosion_particle.hpp"

Explosion::Explosion (const FloatVector2d& arg_pos, Size arg_size)
  : is_drawn (false),
    pos (arg_pos),
    en_size (arg_size)
{
  new_particle_time = 0.0f;

  switch (en_size)
    {
    case SMALL:
      lifetime = .5;
      size = .6;
      break;
    case MEDIUM:
      lifetime = .5;
      size = 1.0f;
      break;
    case LARGE:
      lifetime = 25;
      GameWorld::current()->add(new Shockwave(pos));
      size = 2;
      PingusSound::play_sound("explosion");
      break;
    }

  lifetime = .5f;

  new_particle_time = 1.0f;
}

void
Explosion::draw (View& view)
{
}

void
Explosion::update (float delta)
{
  lifetime -= delta;

  new_particle_time += delta;

  if (new_particle_time > 0.200)
    {
      for (int i = 0; i < 4; ++i)
	{
	  switch (en_size)
	    {
	    case LARGE:
	      GameWorld::current()->add (new ExplosionParticle(FloatVector2d (pos.x + (rand()%40 - 20),
                                                                          pos.y + (rand()%40 - 20)),
                                                               FloatVector2d (rand ()%20 - 10, rand ()%20 - 10),
                                                               Random::frand(size) + 1.0));
	      GameWorld::current()->add (new ExplosionParticle(FloatVector2d (pos.x + (rand()%40 - 20),
                                                                          pos.y + (rand()%40 - 20)),
                                                               FloatVector2d (rand ()%20 - 10, rand ()%20 - 10),
                                                               Random::frand(size) + 1.0));
	      break;

            case MEDIUM:
              GameWorld::current()->add (new ExplosionParticle(FloatVector2d (pos.x + (rand()%10 - 5),
                                                                          pos.y + (rand()%10 - 5)),
                                                               FloatVector2d (rand ()%20 - 10, rand ()%20 - 10),
                                                               Random::frand(size) + .5));
              break;

	    default:
              GameWorld::current()->add (new ExplosionParticle(FloatVector2d (pos.x + (rand()%10 - 5),
                                                                          pos.y + (rand()%10 - 5)),
                                                               FloatVector2d (rand ()%20 - 10, rand ()%20 - 10),
                                                               Random::frand(size) + .01));
	      break;
	    }
	  lifetime = 0;
	}

      new_particle_time = 0;
    }
}

bool
Explosion::removable ()
{
  //std::cout << "Lifetime: " << lifetime << std::endl;

  return lifetime <= 0;
}

float
Explosion::get_z_pos ()
{
  return 115;
}


/* EOF */
