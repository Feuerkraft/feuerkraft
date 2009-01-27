//  $Id: headquarter.hpp,v 1.10 2003/06/22 19:22:56 grumbel Exp $
// 
//  Feuerkraft - A Tank Battle Game
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

#include "../energie.hpp"
#include "building.hpp"
#include "../projectile.hpp"

class Headquarter : public Building
{
private:
  FloatVector2d pos;
  CL_Sprite headquarter;
  CL_Sprite headquarter_damaged;
  CL_Sprite headquarter_destroyed;
  CL_Sprite* current_sur;
  Energie energie;
  bool destroyed;
  
public:
  Headquarter(const AList& lst);
  virtual ~Headquarter();

  void draw(View&);
  void draw_radar(Radar& radar);

  void update (float delta);

  bool is_colliding (FloatVector2d obj_pos);
  void collide (Projectile*);

  int get_map_width ()  { return 2; }
  int get_map_height () { return 2; }

  bool alive ();
};

#endif

/* EOF */
