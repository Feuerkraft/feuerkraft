//  $Id: wall.hxx,v 1.8 2003/05/18 21:15:06 grumbel Exp $
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

#ifndef HEADER_FEUERKRAFT_WALL_HXX
#define HEADER_FEUERKRAFT_WALL_HXX

#include <ClanLib/Display/sprite.h>
#include "../vector2d.hxx"

#include "wall_data.hxx"
#include "building.hxx"

class Wall : public Building
{
private:
  FloatVector2d pos;
  CL_Sprite wall;
  CL_Sprite wall_damaged;
  CL_Sprite wall_destroyed;
  int energie;
public:
  Wall(const WallData&);
  virtual ~Wall();

  void draw (ViewPtr view);
  void draw_radar (RadarPtr radar);

  void update(float);
  void collide (Projectile*);

  int get_map_width ()  { return 1; }
  int get_map_height () { return 1; }

  bool alive ();
};

#endif

/* EOF */
