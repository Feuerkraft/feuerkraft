//  $Id: Tower.hh,v 1.6 2001/05/01 15:06:52 grumbel Exp $
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

#ifndef TOWER_HH
#define TOWER_HH

#include <ClanLib/core.h>
#include "GameObj.hh"
#include "Controllable.hh"
#include "Vehicle.hh"
#include "Energie.hh"

extern CL_ResourceManager* resources;

class Tower : public Controllable,
	      public Vehicle
{
private:
  CL_Surface towerbase;
  CL_Surface towerdamaged;
  CL_Surface towerdestroyed;

  CL_Surface turret;
  
  bool fireing;
  int angle;
  Energie energie;
  bool destroyed;

public:
  Tower (boost::dummy_ptr<GameWorld>  w, float, float);
  virtual ~Tower () 
  {
  }

  virtual void draw (View* view);
  virtual void update (float);

  virtual void start_fire ();
  virtual void stop_fire ();

  virtual void turn_left (float delta) {}
  virtual void turn_right (float delta) {}

  virtual float get_turn_speed () { return 0.0; }
  
  virtual bool is_colliding (CL_Vector obj_pos);
  virtual void collide (Projectile* projectile);

  virtual float get_physical_size () { return 4.0; }
};

#endif

/* EOF */
