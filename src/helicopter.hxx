//  $Id: helicopter.hxx,v 1.10 2003/06/04 10:59:00 grumbel Exp $
// 
//  Feuerkraft - A Tank Battle Game
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

#ifndef HELICOPTER_HH
#define HELICOPTER_HH

#include "game_obj.hxx"
#include "energie.hxx"
#include "vehicle.hxx"

/** @ingroup units */
class Helicopter : public Vehicle
{
private:
  CL_Sprite rotor;
  CL_Sprite heli;
  CL_Sprite heli_shadow;
  CL_Sprite helidestroyed;
  int rotor_count;
  float velocity;
  float angle;
  float strafe;
  bool fireing;
  int reloading;
  Energie energie;
  bool destroyed;

public:
  Helicopter(FloatVector2d);
  ~Helicopter();

  void draw (View& view);
  void update (float);
  float get_z_pos () { return destroyed ? 0 : 150; }

  // Controllable impl
  virtual float get_turn_speed () { return 1.0; }

  virtual void turn_left (float delta);
  virtual void turn_right (float delta);

  virtual void turn_left2 (float delta);
  virtual void turn_right2 (float delta);

  virtual void increase_velocity (float delta);
  virtual void decrease_velocity (float delta);
  virtual void start_fire ();
  virtual void stop_fire ();

  virtual void drop_mine () {}

  bool is_colliding (FloatVector2d);
  void collide (Projectile*);
  virtual float get_physical_size () { return 3.0; }
};

#endif

/* EOF */
