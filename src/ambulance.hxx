//  $Id: ambulance.hxx,v 1.6 2003/06/03 14:11:22 grumbel Exp $
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

#ifndef AMBULANCE_HXX
#define AMBULANCE_HXX

#include <ClanLib/Display/sprite.h>
#include "game_obj.hxx"

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
