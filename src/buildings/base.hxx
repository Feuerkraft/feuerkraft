//  $Id: base.hxx,v 1.3 2003/05/03 16:21:35 grumbel Exp $
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

#ifndef BASE_HH
#define BASE_HH

#include <ClanLib/Display/sprite.h>

#include "../view.hxx"
#include "../boost/dummy_ptr.hpp"
#include "building.hxx"
#include "base_data.hxx"

class Base : public Building,
	     public BaseData
{
private:
  CL_Sprite sprite;
  CL_Vector pos;

public:
  Base (boost::dummy_ptr<GameWorld>  w, const BaseData& data);
  virtual ~Base ();

  void draw (boost::dummy_ptr<View> v);
  void draw_radar (boost::dummy_ptr<Radar> radar);

  void update (float delta);
  
  int get_x_pos () { return x_pos; }
  int get_y_pos () { return y_pos; }

  int get_map_width ()  { return 0; }
  int get_map_height () { return 0; }
};

#endif

/* EOF */
