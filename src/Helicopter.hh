//  $Id: Helicopter.hh,v 1.3 2001/02/21 07:54:33 grumbel Exp $
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
#include "GameObj.hh"
#include "Collideable.hh"
#include "Controllable.hh"
#include "Energie.hh"

class Helicopter : public GameObj,
		   public Controllable,
		   public Collideable
{
private:
  CL_Surface rotor;
  CL_Surface heli;
  CL_Surface helidestroyed;
  CL_Vector pos;
  int rotor_count;
  float velocity;
  float angle;
  float strafe;
  bool fireing;
  int reloading;
  Energie energie;
  bool destroyed;

public:
  Helicopter (CL_Vector);
  ~Helicopter ();

  void draw ();
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
};

#endif

/* EOF */
