//  $Id: Projectile.hxx,v 1.3 2002/03/15 10:32:35 grumbel Exp $
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

#ifndef PROJECTILE_HH
#define PROJECTILE_HH

//#include <ClanLib/Core/Display/surface.h>
#include <ClanLib/display.h>
#include <ClanLib/core.h>
#include "boost/dummy_ptr.hpp"
#include "Vehicle.hxx"

extern CL_ResourceManager* resources;

class Projectile : public Vehicle
{
private:
  CL_Surface sur;
  CL_Vector  tmp_pos;
  CL_Vector  velocity;
  float lifetime;
  
  /** Pointer back to the parent objects which created this
      projectile. Its used to avoid friendly fire (aka shooting
      yourself in the food). */
  boost::dummy_ptr<GameObj> parent;

public:
  Projectile (boost::dummy_ptr<GameWorld>  w, boost::dummy_ptr<GameObj>  p, 
	      const CL_Vector& arg_pos, const CL_Vector& arg_velocity);
  virtual ~Projectile ();

  virtual CL_Vector get_pos () { return pos; }
  virtual void draw (View* view);
  virtual void update (float);
  virtual bool removable ();

  virtual void detonate ();
  bool is_colliding(CL_Vector) { return false;}
};

#endif

/* EOF */
