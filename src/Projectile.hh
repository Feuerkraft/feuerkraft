//  $Id: Projectile.hh,v 1.3 2001/02/20 22:49:01 grumbel Exp $
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
#include <ClanLib/core.h>
#include "GameObj.hh"

extern CL_ResourceManager* resources;

class Projectile : public GameObj
{
private:
  CL_Surface sur;
  CL_Vector  pos;
  CL_Vector  tmp_pos;
  CL_Vector  add;
  int lifetime;
  int active;

public:
  Projectile (const CL_Vector& arg_pos, const CL_Vector& arg_add);
  virtual ~Projectile ();

  virtual CL_Vector get_pos () { return pos; }
  virtual void draw ();
  virtual void update (float);
  virtual bool removable ();

  virtual void detonate ();
};

#endif

/* EOF */
