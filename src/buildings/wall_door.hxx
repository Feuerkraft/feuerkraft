//  $Id: wall_door.hxx,v 1.9 2003/06/03 14:11:22 grumbel Exp $
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

#ifndef WALLDOOR_HXX
#define WALLDOOR_HXX

#include <ClanLib/Display/sprite.h>
#include <ClanLib/Core/Math/cl_vector.h>

#include "building.hxx"
#include "../vector2d.hxx"
#include "wall_door_data.hxx"

class View;
class Radar;
class Projectile;

class WallDoor : public Building
{
private:
  CL_Sprite sprite;
  int map_width;
  int map_height;
  typedef enum { S_OPENED, S_CLOSED } Status;
  Status status;
  
  /** Just for caching purpose */
  FloatVector2d pos;

public:
  WallDoor(const WallDoorData&);
  virtual ~WallDoor();

  void draw (View& view);
  void draw_radar (Radar& radar);

  void update(float);
  void collide (Projectile*);

  int get_map_width ()  { return map_width; }
  int get_map_height () { return map_height; }

  bool is_active ();
  bool alive ();
};

#endif

/* EOF */
