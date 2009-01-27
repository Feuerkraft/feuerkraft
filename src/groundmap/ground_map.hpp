//  $Id: ground_map.hxx,v 1.5 2003/06/03 14:11:22 grumbel Exp $
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

#ifndef GROUNDMAP_HXX
#define GROUNDMAP_HXX

#include "../view.hxx"
#include "../game_obj.hxx"
#include "ground_type.hxx"

/** The GroundMap interface defines the basic interaction between
    vehicles and the ground. It allows a GameObj to know what the
    current groundtype is and similar things
*/
class GroundMap : public GameObj
{
private:

public:
  GroundMap ()
  {
  }

  /** Return the type of ground, x and y are in world coordinates */
  virtual GroundType get_groundtype (float x, float y) =0;

  float get_z_pos () { return -5; }
};

#endif

/* EOF */
