//  $Id: background.hxx,v 1.3 2003/04/28 19:42:59 grumbel Exp $
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

#ifndef FEUERKRAFT_BACKGROUND_HH
#define FEUERKRAFT_BACKGROUND_HH

#include <ClanLib/core.h>
#include <ClanLib/display.h>
#include "game_obj.hxx"

/** should be moved to groundmaps/.. and renamed to BaseGroundMap or
    something like that */
class Background 
  : public GameObj
{
private:
  CL_Surface sur;
  
public:
  Background (boost::dummy_ptr<GameWorld> w, const CL_Sprite& sprite);
  virtual ~Background () {}

  void draw (View* draw);
  void update (float delta) {}

  virtual int  get_z_pos () { return -10; }
};

#endif

/* EOF */
