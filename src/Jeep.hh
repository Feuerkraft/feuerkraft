//  $Id: Jeep.hh,v 1.3 2001/11/28 17:17:27 grumbel Exp $
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

#ifndef JEEP_HH
#define JEEP_HH

#include <ClanLib/core.h>
#include <SphriteLib/sphritelibGL.h>
#include "Mine.hh"
#include "Vehicle.hh"
#include "Controllable.hh"
#include "Energie.hh"
#include "GameObj.hh"
#include "Flag.hh"

class Jeep : public Controllable,
	     public Vehicle
{
private:
  SpriteProviderStorage storage;
  Sprite* jeep;

  Energie energie;
  float velocity;
  float angle;
  Flag* flag;
public:
  Jeep (boost::dummy_ptr<GameWorld>  w, CL_Vector arg_pos);
  virtual ~Jeep () {}
  
  void update (float delta);
  void draw (View* view);

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

  virtual bool is_colliding (CL_Vector obj_pos);
  virtual void collide (Mine*);
  virtual void collide (Projectile*);
  virtual void collide (CL_Vector force);

  virtual int get_z_pos () { return 50; }
  
  void add_flag (Flag* flag);
  virtual float get_physical_size () { return 2.0; }
};

#endif

/* EOF */
