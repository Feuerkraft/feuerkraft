//  $Id: Shockwave.cc,v 1.3 2001/02/24 20:32:13 grumbel Exp $
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

#include "Shockwave.hh"

Shockwave::Shockwave (CL_Vector arg_pos) :
  pos (arg_pos),
  sur ("feuerkraft/shockwave", resources),
  counter (0)
{
}

Shockwave::~Shockwave ()
{
}

template<class T> 
T mid (T min, T some, T max)
{
  return std::min(std::max(min, some), max);
}

void 
Shockwave::draw (View* view)
{
  float size = counter / 15.0 + 0.5;
  int frame = mid(0, int((counter)/ (30/4.0)), 3);

  sur.put_screen (pos.x - (sur.get_width () * size)/2,
		  pos.y - (sur.get_height () * size)/2,
		  size, size, frame);
}

void 
Shockwave::update (float delta)
{
  counter += 3;
  if (counter >= 30)
    remove ();
}

/* EOF */
