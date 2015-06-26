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

#ifndef HEADER_ROCKET_SMOKE_PARTICLE_HXX
#define HEADER_ROCKET_SMOKE_PARTICLE_HXX

#include "particle.hpp"

/** */
class RocketSmokeParticle : public Particle
{
private:
  float max_life_time;
  float size;
  float angle;
  CL_Sprite sprite;

public:
  RocketSmokeParticle(const FloatVector2d& arg_pos);
  ~RocketSmokeParticle();
private:
  RocketSmokeParticle (const RocketSmokeParticle&);
  RocketSmokeParticle& operator= (const RocketSmokeParticle&);

  void update (float delta);
  void draw (View& view);
  float get_z_pos ();
};

#endif

/* EOF */
