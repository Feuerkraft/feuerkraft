//  $Id: Tower.hh,v 1.1 2001/02/17 20:02:12 grumbel Exp $
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
#include "Collideable.hh"
#include "Energie.hh"

extern CL_ResourceManager* resources;

class Tower : public Controllable,
	      public GameObj,
	      public Collideable
{
private:
  CL_Surface towerbase;
  CL_Surface turret;
  
  CL_Vector pos;
  bool fireing;
  int angle;
  Energie energie;
  
public:
  Tower (float arg_x_pos, float arg_y_pos) :
    towerbase ("feuerkraft/towerbase", resources),
    turret ("feuerkraft/towerturret", resources),
    pos (arg_x_pos, arg_y_pos),
    fireing (true),
    angle (0),
    energie (100)    
  {
  }
  
  virtual ~Tower () 
  {
  }

  virtual void draw ();
  virtual void update ();

  virtual void start_fire ();
  virtual void stop_fire ();

  virtual void turn_left () {}
  virtual void turn_right () {}

  virtual float get_turn_speed () { return 0.0; }
  
  virtual bool is_colliding (CL_Vector obj_pos);
  virtual void collide (Projectile* projectile);
};

#endif

/* EOF */
