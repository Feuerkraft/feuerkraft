//  $Id: mine.hxx,v 1.1 2003/04/19 22:39:07 grumbel Exp $
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
#include <ClanLib/display.h>
#include "GameObj.hxx"
#include "Explosion.hxx"

class Mine : public GameObj
{
private:
  CL_Sprite sur;
  CL_Sprite sur_active;
  CL_Vector pos;
  CL_Sprite hole;
  float active;
  bool detonated;
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
