//  $Id: headquarter.hxx,v 1.5 2003/05/11 11:20:45 grumbel Exp $
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

#include "../boost/dummy_ptr.hpp"
#include "../energie.hxx"
#include "building.hxx"
#include "headquarter_data.hxx"
#include "../projectile.hxx"

class Headquarter : public Building
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
  Headquarter(const HeadquarterData&);
  virtual ~Headquarter();

  void draw (boost::dummy_ptr<View>);
  void draw_radar (boost::dummy_ptr<Radar> radar);

  void update (float delta);

  bool is_colliding (CL_Vector obj_pos);
  void collide (Projectile*);

  int get_map_width ()  { return 2; }
  int get_map_height () { return 2; }

  bool alive ();
};

#endif

/* EOF */
