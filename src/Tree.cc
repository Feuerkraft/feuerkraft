//  $Id: Tree.cc,v 1.4 2001/05/04 17:40:11 grumbel Exp $
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

#include "Tree.hh"

Tree::Tree (boost::dummy_ptr<GameWorld>  w,
	    CL_Vector arg_pos, std::string name) 
  : GameObj (w),
    pos (arg_pos),
    sur (name.c_str (), resources)
{
}

Tree::~Tree ()
{
}
  
void 
Tree::draw (View* view)
{
  view->draw (sur, 
	      pos.x - sur.get_width ()/2, 
	      pos.y - sur.get_height ()/2);
  view->draw_circle (pos.x, pos.y, 7,
		     1.0f, 1.0f, 1.0f);
}

/* EOF */
