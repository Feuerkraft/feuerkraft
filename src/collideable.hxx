//  $Id: collideable.hxx,v 1.1 2003/04/19 22:39:06 grumbel Exp $
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

#ifndef COLLIDEABLE_HH
#define COLLIDEABLE_HH

#include <ClanLib/core.h>
#include "GameObj.hxx"
//#include "Projectile.hxx"

class Projectile;

class Collideable : public GameObj
{
private:
  
public:
  Collideable (boost::dummy_ptr<GameWorld>  w) : GameObj (w) {};
  virtual ~Collideable () {};

  /** Check if the collideable is colliding with a object at obj_pos */
  virtual bool is_colliding (CL_Vector obj_pos) =0;

  /** Let the object collide with a Projectile, probally not usefull */
  virtual void collide (Projectile*) {}

  virtual void collide (CL_Vector force) {}
};

#endif

/* EOF */
