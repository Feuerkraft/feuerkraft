//  $Id: Shockwave.hh,v 1.1 2001/02/18 15:27:25 grumbel Exp $
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

#ifndef SHOCKWAVE_HH
#define SHOCKWAVE_HH

#include <ClanLib/core.h>
#include "GameObj.hh"

extern CL_ResourceManager* resources;

class Shockwave : public GameObj
{
private:
  CL_Vector pos;
  CL_Surface sur;
  int counter;
public:
  Shockwave (CL_Vector arg_pos);
  virtual ~Shockwave ();

  void draw ();
  void update ();
  int  get_z_pos () { return -1; }
};

#endif

/* EOF */
