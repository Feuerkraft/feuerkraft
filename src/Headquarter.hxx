//  $Id: Headquarter.hxx,v 1.1 2001/12/12 00:00:32 grumbel Exp $
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

#ifndef HEADQUARTER_HH
#define HEADQUARTER_HH

#include <ClanLib/core.h>
#include <ClanLib/display.h>
#include "boost/dummy_ptr.hpp"
#include "GameObj.hxx"
#include "Energie.hxx"
#include "Collideable.hxx"

class Headquarter : public Collideable
{
private:
  CL_Vector pos;
  CL_Surface headquarter;
  CL_Surface headquarter_damaged;
  CL_Surface headquarter_destroyed;
  boost::dummy_ptr<CL_Surface> current_sur;
  Energie energie;
  bool destroyed;
  
public:
  Headquarter (boost::dummy_ptr<GameWorld> world, CL_Vector arg_pos);
  virtual ~Headquarter ();

  void update (float delta);
  void draw (View* view);
  bool is_colliding (CL_Vector obj_pos);
  void collide (Projectile*);
};

#endif

/* EOF */
