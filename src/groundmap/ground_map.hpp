//  $Id: ground_map.hpp,v 1.5 2003/06/03 14:11:22 grumbel Exp $
//
//  Feuerkraft - A Tank Battle Game
//  Copyright (C) 2000 Ingo Ruhnke <grumbel@gmx.de>
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.

#ifndef GROUNDMAP_HXX
#define GROUNDMAP_HXX

#include "../view.hpp"
#include "../game_obj.hpp"
#include "ground_type.hpp"

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
