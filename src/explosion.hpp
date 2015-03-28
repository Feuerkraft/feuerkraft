//  $Id: explosion.hpp,v 1.8 2003/06/06 09:49:00 grumbel Exp $
//
//  Feuerkraft - A Tank Battle Game
//  Copyright (C) 2000 Ingo Ruhnke <grumbel@gmx.de>
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

#ifndef EXPLOSION_HH
#define EXPLOSION_HH

#include "vector2d.hpp"
#include "game_obj.hpp"
#include "resource_manager.hpp"

/** Particle emmitter for ExplosionParticles */
class Explosion : public GameObj
{
private:
  bool is_drawn;
  float lifetime;
  FloatVector2d pos;
  float new_particle_time;
  float size;
public:
  enum Size { SMALL, MEDIUM, LARGE } en_size;

  Explosion (const FloatVector2d& arg_pos, Size arg_size = SMALL);
  void init ();

  void draw (View& view);
  void update (float);
  bool removable ();
  float get_z_pos ();
};

#endif

/* EOF */
