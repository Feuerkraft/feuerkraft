//  $Id: tower.hxx,v 1.11 2003/06/22 19:22:56 grumbel Exp $
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

#ifndef TOWER_HXX
#define TOWER_HXX

#include <ClanLib/Display/sprite.h>
#include "../energie.hxx"
#include "../unit.hxx"
#include "building.hxx"

class Controller;
class GameWorld;

class Tower : public Building,
              public Unit
{
private:
  CL_Sprite towerbase;
  CL_Sprite towerdamaged;
  CL_Sprite towerdestroyed;
  CL_Sprite turret;
  
  float steering;
  float orientation;
  Energie energie;
  bool destroyed;

  /** The position is just for easier handling here, the real position
      is due to the position in the building map */
  FloatVector2d pos;
public:
  Tower(const AList& lst);
  virtual ~Tower();
  
  // Draw the object onto the screen
  void draw (View& view);
  void draw_energie (View& view);
  void draw_radar (Radar& radar);

  // Update the object once a game loop
  void update (float);
  
  void update_controlls(const Controller& controller);

  int get_map_width ()  { return 2; }
  int get_map_height () { return 2; }

  void collide (Projectile*);
  void collide (int energie);

  float get_orientation() const { return orientation; }
  bool alive ();
};

#endif

/* EOF */
