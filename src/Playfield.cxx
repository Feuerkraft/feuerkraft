//  $Id: Playfield.cxx,v 1.1 2001/12/12 00:00:33 grumbel Exp $
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
#include <ClanLib/display.h>
#include "Playfield.hxx"

Playfield::Playfield (boost::dummy_ptr<GameWorld>  w)
  : GameObj (w)
{
}

void 
Playfield::draw (View* view)
{
  CL_Display::fill_rect (0, 0, 
			 CL_Display::get_width (),
			 CL_Display::get_height (),
			 0.7f, 0.7f, 0.6f);
}

/* EOF */
