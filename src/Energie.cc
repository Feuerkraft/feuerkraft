//  $Id: Energie.cc,v 1.1 2001/02/17 20:02:11 grumbel Exp $
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

#include <ClanLib/core.h>
#include "Energie.hh"

Energie::Energie (int arg_energie) :
  max_energie (arg_energie),
  energie (arg_energie)
{
  
}

void
Energie::draw (int x_pos, int y_pos)
{
  CL_Display::fill_rect (x_pos - 32, y_pos - 5,
			 x_pos + 32, y_pos + 5,
			 0.0, 0.0, 0.0, 0.3);
  CL_Display::fill_rect (x_pos - 30, y_pos - 3,
			 x_pos - 30 + (energie * 60 / max_energie), y_pos + 3,
			 0.0, 1.0, 0.0, 0.5);
}

/* EOF */
