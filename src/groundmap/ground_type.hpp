//  $Id: ground_type.hpp,v 1.3 2003/06/03 14:11:22 grumbel Exp $
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

#ifndef GROUNDTYPE_HXX
#define GROUNDTYPE_HXX

#include <string>

/** The GroundType defines the type of the ground, it has influence on
    the speed and acceleration of vehicles. It has also influence on
    the detonation type of shells and rocket (splash instead of a big
    explosion and such). 

    FIXME: GroundType<->Palette relation is hardcoded
*/
enum GroundType 
{ 
  /** This GroundType is used to mark empty tiles, vehicles should not
      react and it and the Worlds groundmap must not return it,
      instead it should fallback to the default value for the current
      map. */
  GT_EMPTY,
  
  /** Wheel driven vehicles will be slower on this ground type, chain
      driven vehicles won't be much influenced by this */
  GT_SAND,

  /** FIXME: description */
  GT_GRASS,

  /** FIXME: description */
  GT_MUD,

  /** All vehicles can drive in flatwater, but some will seriously
      slow down */
  GT_FLATWATER,

  /** Land vehicle can't drive here, only ships and hovercrafts */
  GT_DEEPWATER,

  /** Street and parking places have the GroundType GT_ASPHALT, wheel
      vehicles will be fast on here. */
  GT_ASPHALT, 

  /** also known Dark sand */
  GT_WETSAND
};

std::string GroundType2string(const GroundType& a);

#endif

/* EOF */
