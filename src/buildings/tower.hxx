//  $Id: tower.hxx,v 1.5 2003/05/11 11:20:45 grumbel Exp $
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

#ifndef TOWER_HXX
#define TOWER_HXX

#include <ClanLib/Display/sprite.h>
#include "../energie.hxx"
#include "building.hxx"
#include "tower_data.hxx"

class GameWorld;

class Tower : public Building
{
private:
  CL_Sprite towerbase;
  CL_Sprite towerdamaged;
  CL_Sprite towerdestroyed;
  CL_Sprite turret;
  
  float angle;
  Energie energie;
  bool destroyed;

  /** The position is just for easier handling here, the real position
      is due to the position in the building map */
  CL_Vector pos;
public:
  Tower(const TowerData& data);
  virtual ~Tower();
  
  // Draw the object onto the screen
  void draw (boost::dummy_ptr<View> view);
  void draw_energie (boost::dummy_ptr<View> view);
  void draw_radar (boost::dummy_ptr<Radar> radar);

  // Update the object once a game loop
  void update (float);
  
  int get_map_width ()  { return 2; }
  int get_map_height () { return 2; }

  void collide (Projectile*);

  bool alive ();
};

#endif

/* EOF */
