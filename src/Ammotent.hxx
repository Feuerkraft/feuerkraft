//  $Id: Ammotent.hxx,v 1.1 2001/12/12 00:00:32 grumbel Exp $
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

#ifndef AMMOTENT_HH
#define AMMOTENT_HH

#include <ClanLib/core.h>
#include <ClanLib/display.h>
#include "boost/dummy_ptr.hpp"
#include "View.hxx"
#include "GameObj.hxx"

class Ammotent : public GameObj
{
private:
  CL_Surface ammotent;
  CL_Vector pos;

public:
  Ammotent (boost::dummy_ptr<GameWorld> world, CL_Vector arg_pos);
  virtual ~Ammotent ();

  void draw (View* );
  void update (float delta);  
};

#endif

/* EOF */
