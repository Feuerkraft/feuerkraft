//  $Id: tank.hxx,v 1.8 2003/05/18 23:01:49 grumbel Exp $
// 
//  Pingus - A free Lemmings clone
//  Copyright (C) 2000 Ingo Ruhnke <grumbel@gmx.de>
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

#ifndef TANK_HH
#define TANK_HH

#include <ClanLib/Display/sprite.h>
#include "vector2d.hxx"
#include <deque>

#include "mine.hxx"
#include "game_obj.hxx"
#include "controllable.hxx"
#include "energie.hxx"
#include "vehicle.hxx"

/** \defgroup units Units - Player Controllable GameObjs */

class Turret;

/** \brief A track vehicle with a turret
    \ingroup units 

    A Tank is a tack vehicle with a turret, parameters such as
    velocity, ammount of ammunition and other things are
    configurable...
*/
class Tank : public Controllable,
	     public Vehicle
{
private:
  float orientation; //rad
  float speed;
  float velocity;
  float increment;
  int frame;

  /*CL_Surface sur;*/
  CL_Sprite smod;
  CL_Sprite sur_destroyed;

  CL_Sprite sur;
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
  
public:
  friend class Turret;

  Tank (const FloatVector2d &arg_pos,
	int reloading_speed, std::string tank, std::string turret, std::string fire);
  virtual ~Tank ();
  
  void draw (View* view);
  void draw_energie (View* view);
  void draw_levelmap (LevelMap* levelmap);

  void update (float);

  void explode ();

  void increase_angle (float delta);
  void decrease_angle (float delta);
  void set_angle (float);
  Turret* get_turret () { return turret; }

  float get_orientation() { return orientation; }
  float get_increment() { return increment; }

  // Implementing Controllable
  float get_acceleration () { return increment; }
  float get_max_forward_velocity () { return 1.0; }
  float get_max_backward_velocity () { return -1.0; }
  float get_turn_speed () { return 1.0; }

  void turn_left (float delta) { decrease_angle (delta); }
  void turn_right (float delta) { increase_angle (delta); }

  void turn_left2 (float delta);
  void turn_right2 (float delta);

  void increase_velocity (float delta);
  void decrease_velocity (float delta);
  
  void start_fire ();
  void stop_fire ();

  void drop_mine ();
  
  int get_z_pos () { return destroyed ? 0 : 50; }

  bool is_colliding (FloatVector2d obj_pos);

  void on_collision(GameObj* obj);
  void on_collision_with_building(Building* building);

  void collide (Projectile*);
  void collide (Mine*);
  virtual void collide (FloatVector2d force);

  virtual float get_physical_size () { return 3.0; }
  float get_velocity ();

  /** FIXME: This should be placed in a Player-Manager class or
      something like that */
  void respawn ();
};

#endif // TANK_HH

// EOF
