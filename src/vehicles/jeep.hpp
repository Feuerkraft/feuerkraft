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

#ifndef JEEP_HH
#define JEEP_HH

#include <ClanLib/Display/sprite.h>

#include "../energie.hpp"
#include "vehicle.hpp"

class Projectile;

/** @ingroup units */
class Jeep : public Vehicle
{
private:
  CL_Sprite jeep;

  Energie energie;
  float velocity;
  float angle;

public:
  Jeep (FloatVector2d arg_pos);
  virtual ~Jeep () {}

  void update (float delta);
  void draw (View& view);

  // Controllable
  virtual float get_turn_speed () { return 0.0; }

  virtual void turn_left (float delta);
  virtual void turn_right (float delta);

  virtual void turn_left2 (float delta);
  virtual void turn_right2 (float delta);

  virtual void increase_velocity (float delta);
  virtual void decrease_velocity (float delta);
  virtual void start_fire ();
  virtual void stop_fire ();

  virtual void drop_mine ();

  virtual bool is_colliding (FloatVector2d obj_pos);
  virtual void collide (Projectile*);
  virtual void collide (FloatVector2d force);

  virtual float get_z_pos () { return 50; }

  virtual float get_physical_size () { return 2.0; }
};

#endif

/* EOF */
