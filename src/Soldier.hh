//  $Id: Soldier.hh,v 1.4 2001/03/16 20:36:06 grumbel Exp $
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

#ifndef SOLDIER_HH
#define SOLDIER_HH

#include <ClanLib/display.h>
#include "GameObj.hh"

extern CL_ResourceManager* resources;

class Soldier : public GameObj
{
private:
  CL_Surface sur;
  CL_Vector  pos;
  int frame;
  int step;
public:
  Soldier (const CL_Vector& arg_pos);
  ~Soldier ();

  void draw (View* view);
  void update (float);
};

#endif

/* EOF */
