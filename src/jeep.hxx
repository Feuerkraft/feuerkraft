//  $Id: jeep.hxx,v 1.9 2003/06/03 14:11:22 grumbel Exp $
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

#ifndef JEEP_HH
#define JEEP_HH

#include <ClanLib/Display/sprite.h>

#include "vehicle.hxx"
#include "controllable.hxx"
#include "energie.hxx"
#include "game_obj.hxx"

class Projectile;

/** @ingroup units */
class Jeep : public Controllable,
	     public Vehicle
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
