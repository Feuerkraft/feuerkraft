//  $Id: projectile.hpp,v 1.11 2003/06/03 14:11:22 grumbel Exp $
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

#ifndef PROJECTILE_HH
#define PROJECTILE_HH

#include "vector2d.hpp"
#include "game_obj.hpp"
#include "resource_manager.hpp"

class Projectile : public GameObj
{
private:
  FloatVector2d pos;
  CL_Sprite sur;
  CL_Sprite sur_light;
  FloatVector2d tmp_pos;
  FloatVector2d velocity;
  float lifetime;
  
  /** Pointer back to the parent objects which created this
      projectile. Its used to avoid friendly fire (aka shooting
      yourself in the food). */
  GameObj* parent;

public:
  Projectile(GameObj* p, const FloatVector2d& arg_pos, const FloatVector2d& arg_velocity);
  virtual ~Projectile();

  virtual FloatVector2d get_pos () { return pos; }

  GameObj* get_parent() const { return parent; }

  void draw (View& view);
  void update (float);
  bool removable ();

  void on_collision(GameObj* obj);
  void on_collision_with_building(Building* building);

  void detonate ();
  bool is_colliding(FloatVector2d) { return false;}

private:
  Projectile(const Projectile&);
  Projectile& operator=(const Projectile&);
};

#endif

/* EOF */
