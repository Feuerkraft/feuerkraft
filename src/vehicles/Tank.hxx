//  $Id: Tank.hxx,v 1.2 2002/07/04 09:50:03 grumbel Exp $
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

#ifndef TANK_HXX
#define TANK_HXX

#include "TankData.hxx"

/** Parent class for MammutTank and FoxTank, its in the hope they both
    will share quite a bit of code */
class Tank : public GameObj
{
private:
  TankData current_state;
  TankData next_state;

public:
  Tank ();
  
  /** Update all generic tank data */
  void update (const GameDelta& delta);
  
  /** copy next_state over current_state */
  void flip ();
};

#endif

/* EOF */
