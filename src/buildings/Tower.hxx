//  $Id: Tower.hxx,v 1.2 2002/03/17 00:16:50 grumbel Exp $
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

#include <SphriteLib/sphritelib.h>
#include "../Energie.hxx"
#include "Building.hxx"
#include "TowerData.hxx"

class GameWorld;

class Tower : public Building,
	      public TowerData
{
private:
  Sprite towerbase;
  Sprite towerdamaged;
  Sprite towerdestroyed;
  Sprite turret;
  
  Energie energie;
  bool destroyed;

  /** The position is just for easier handling here, the real position
      is due to the position in the building map */
  CL_Vector pos;
public:
  Tower (GameWorld*, const TowerData& data);
  
  // Draw the object onto the screen
  void draw (boost::dummy_ptr<View> view);

  // Update the object once a game loop
  void update (float);
};

#endif

/* EOF */
