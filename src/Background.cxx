//  $Id: Background.cxx,v 1.3 2002/04/02 09:52:56 grumbel Exp $
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

#include "View.hxx"
#include "Background.hxx"


Background::Background (boost::dummy_ptr<GameWorld> w,
			const CL_Surface& arg_sur)
  : GameObj (w),
    sur (arg_sur)
{
}

void
Background::draw (View* view)
{
  // FIXME: We should take the view size into account

  //FIXME:Display2
  /*  
  for (int y = -1; y <= 1; ++y)
    for (int x = -1; x <= 1; ++x)
      sur.put_screen ((x * sur.get_width()) + view->get_x_offset () % sur.get_width (),
		      (y * sur.get_height()) + view->get_y_offset () % sur.get_height ());
  */
}

/* EOF */
