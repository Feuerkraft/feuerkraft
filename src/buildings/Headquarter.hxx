//  $Id: Headquarter.hxx,v 1.5 2002/07/21 19:32:31 grumbel Exp $
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

#ifndef HEADQUARTER_HH
#define HEADQUARTER_HH

#include <ClanLib/core.h>
#include <ClanLib/display.h>

#include "../boost/dummy_ptr.hpp"
#include "../Energie.hxx"
#include "Building.hxx"
#include "HeadquarterData.hxx"
#include "../Projectile.hxx"

class Headquarter : public Building,
		    public HeadquarterData
{
private:
  CL_Vector pos;
  CL_Sprite headquarter;
  CL_Sprite headquarter_damaged;
  CL_Sprite headquarter_destroyed;
  boost::dummy_ptr<CL_Sprite> current_sur;
  Energie energie;
  bool destroyed;
  
public:
  Headquarter (boost::dummy_ptr<GameWorld> world, const HeadquarterData&);
  virtual ~Headquarter ();

  void draw (boost::dummy_ptr<View>);
  void draw_radar (boost::dummy_ptr<Radar> radar);

  void update (float delta);

  bool is_colliding (CL_Vector obj_pos);
  void collide (Projectile*);

  int get_x_pos () { return x_pos; }
  int get_y_pos () { return y_pos; }

  int get_map_width ()  { return 2; }
  int get_map_height () { return 2; }

  bool alive ();
};

#endif

/* EOF */
