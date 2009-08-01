//  $Id: ambulance.hpp,v 1.7 2003/06/04 10:59:00 grumbel Exp $
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

#ifndef AMBULANCE_HXX
#define AMBULANCE_HXX

#include <ClanLib/Display/sprite.h>
#include "game_obj.hpp"

class Ambulance : public GameObj
{
private:
  CL_Sprite sur;

public:
  Ambulance();

  // Draw the object onto the screen
  void draw (View& view);
   
};

#endif

/* EOF */
