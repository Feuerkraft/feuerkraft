//  $Id: shockwave.hxx,v 1.1 2003/04/19 22:39:07 grumbel Exp $
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
#include <ClanLib/display.h>
#include "GameObj.hxx"
#include "ResourceManager.hxx"

class Shockwave : public GameObj
{
private:
  CL_Vector pos;
  CL_Sprite sprite;
  float progress;
public:
  Shockwave (boost::dummy_ptr<GameWorld>  w, CL_Vector arg_pos);
  virtual ~Shockwave ();

  void draw (View* view);
  void update (float);
  int  get_z_pos () { return -1; }
};

#endif

/* EOF */
