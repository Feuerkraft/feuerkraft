//  $Id: WallDoor.hxx,v 1.1 2002/03/28 01:50:46 grumbel Exp $
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

#ifndef WALLDOOR_HXX
#define WALLDOOR_HXX

#include <SphriteLib/sphritelib.h>
#include <ClanLib/core.h>
#include "boost/dummy_ptr.hpp"
#include "Building.hxx"
#include "WallDoorData.hxx"

class View;
class Radar;
class Projectile;

class WallDoor : public Building,
		 public WallDoorData
{
private:
  Sprite sprite;
  CL_Vector pos;
  int map_width;
  int map_height;
  typedef enum { S_OPENED, S_CLOSED } Status;
  Status status;

public:
  WallDoor (boost::dummy_ptr<GameWorld> world, const WallDoorData&);
  virtual ~WallDoor ();

  void draw (boost::dummy_ptr<View> view);
  void draw_radar (boost::dummy_ptr<Radar> radar);

  void update(float);
  void collide (Projectile*);

  int get_x_pos () { return x_pos; }
  int get_y_pos () { return y_pos; }

  int get_map_width ()  { return map_width; }
  int get_map_height () { return map_height; }

  bool alive ();
};

#endif

/* EOF */
