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

#ifndef TANK_HH
#define TANK_HH

#include <deque>
#include <ClanLib/Display/sprite.h>
#include "../vector2d.hpp"

#include "../mine.hpp"
#include "../energie.hpp"
#include "vehicle.hpp"

/** \defgroup units Units - Player Controllable GameObjs */

class VehicleAI;
class AList;
class SmokeEmitter;
class Projectile;
class Turret;

/** \brief A track vehicle with a turret
    \ingroup units

    A Tank is a tack vehicle with a turret, parameters such as
    velocity, ammount of ammunition and other things are
    configurable...
*/
class Tank : public Vehicle
{
private:
  /** Position of the tank, before the last update() */
  FloatVector2d tmp_pos;

  float speed;

  /** The maximum turn speed of the turret */
  float increment;

  int frame;
  bool burning;

  /*CL_Surface sur;*/
  CL_Sprite smod;
  CL_Sprite sur_destroyed;

  CL_Sprite sur;
  CL_Sprite sur_light;
  CL_Sprite sur_highlight;
  CL_Sprite shadow;

  Turret* turret;

  std::deque<FloatVector2d> smodpos;
  float tmp_angle;
  int smod_step;
  int mine_reload_time;
  Energie energie;
  bool destroyed;
  float particle_release;
  /** time since destruction */
  int destroy_time;

  SmokeEmitter* smoke_emitter;
  VehicleAI* ai;
public:
  friend class Turret;

  Tank (const AList& lst);
  Tank (const FloatVector2d &arg_pos,
	int reloading_speed, std::string tank, std::string turret, std::string fire);
  virtual ~Tank ();

  void draw (View& view);
  void draw_energie (View& view);
  void draw_levelmap (LevelMap& levelmap);

  void update (float);

  void explode ();

  void set_angle (float);
  Turret* get_turret () { return turret; }

  float get_increment() { return increment; }

  // Implementing Controllable
  float get_acceleration () { return increment; }
  float get_max_forward_velocity () { return 1.0; }
  float get_max_backward_velocity () { return -1.0; }
  float get_turn_speed () { return 1.0; }

  void drop_mine ();

  float get_z_pos () { return destroyed ? 0 : 50; }

  bool is_colliding (FloatVector2d obj_pos);

  void on_collision(GameObj* obj);
  void on_collision_with_building(Building* building);

  void collide (Projectile*);
  void collide (Mine*);
  virtual void collide (FloatVector2d force);

  virtual float get_physical_size () { return 3.0; }

  /** FIXME: This should be placed in a Player-Manager class or
      something like that */
  void respawn ();
  void attach_ai();
  void dettach_ai();

private:
  Tank(const Tank&);
  Tank& operator=(const Tank&);
};

#endif // TANK_HH

// EOF
