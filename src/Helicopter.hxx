//  $Id: Helicopter.hxx,v 1.4 2002/07/21 19:32:31 grumbel Exp $
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

#ifndef HELICOPTER_HH
#define HELICOPTER_HH

#include <ClanLib/core.h>
#include <ClanLib/display.h>

#include "GameObj.hxx"
#include "Collideable.hxx"
#include "Controllable.hxx"
#include "Energie.hxx"
#include "Vehicle.hxx"

class Helicopter : public Controllable,
		   public Vehicle
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
  Helicopter (boost::dummy_ptr<GameWorld>, CL_Vector);
  ~Helicopter ();

  void draw (View* view);
  void update (float);
  int get_z_pos () { return destroyed ? 0 : 150; }

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

  bool is_colliding (CL_Vector);
  void collide (Projectile*);
  virtual float get_physical_size () { return 3.0; }
};

#endif

/* EOF */
