//  $Id: Mine.hxx,v 1.1 2001/12/12 00:00:33 grumbel Exp $
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

#ifndef MINE_HH
#define MINE_HH

#include <ClanLib/core.h>
#include "GameObj.hxx"
#include "Explosion.hxx"

extern CL_ResourceManager* resources;

class Mine : public GameObj
{
private:
  CL_Surface sur;
  CL_Surface sur_active;
  CL_Vector pos;
  int active;
  
public:
  Mine (boost::dummy_ptr<GameWorld>, const CL_Vector& arg_pos);
  virtual ~Mine () {}

  CL_Vector get_pos () { return pos; }
  void update (float);
  void draw (View* view);
  void detonate ();
  bool is_active ();
};

#endif

/* EOF */
