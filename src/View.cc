//  $Id: View.cc,v 1.5 2001/05/01 22:48:43 sphair Exp $
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
#include "View.hh"

View::View (boost::dummy_ptr<GameWorld> arg_world, 
	    int arg_x1, int arg_y1, 
	    int arg_x2, int arg_y2,
	    int arg_x_offset, int arg_y_offset) :
  world (arg_world), x1 (arg_x1), y1 (arg_y1), x2 (arg_x2), y2 (arg_y2),
  x_offset (-arg_x_offset), y_offset (-arg_y_offset)
{
  x_offset -= x1;
  y_offset -= y1;
}

View::~View ()
{
}

void 
View::update (float delta)
{
  // nothing to do
}

void 
View::draw ()
{
  //std::cout << "Drawing: " << x_offset << " " << y_offset << std::endl;
  CL_Display::push_clip_rect (CL_ClipRect (x1, y1, x2, y2));
  world->draw (this);
  CL_Display::pop_clip_rect ();
}

int View::get_x_offset () { return x1 - x_offset + (x2 - x1)/2; }
int View::get_y_offset () { return y1 - y_offset + (y2 - y1)/2; }
int View::get_x1 () { return x1; }
int View::get_x2 () { return x2; }
int View::get_y1 () { return y1; }
int View::get_y2 () { return y2; }

void 
View::set_view (int x_pos, int y_pos)
{
  x_offset = x_pos;
  y_offset = y_pos;
}

/* EOF */
