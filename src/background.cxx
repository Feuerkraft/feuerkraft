//  $Id: background.cxx,v 1.12 2003/06/03 14:11:22 grumbel Exp $
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

#include "view.hxx"
#include "background.hxx"


Background::Background (const CL_Sprite& arg_sprite,
                        float arg_z_pos)
  : sur (arg_sprite.get_frame_surface(0)),
    z_pos(arg_z_pos)
{
  sur.set_alignment(origin_top_left);
}

void
Background::draw (View& view)
{
  // FIXME: We should take the view size and surface size into account
  for (int y = -1; y <= 2; ++y)
    for (int x = -1; x <= 2; ++x)
      sur.draw(x * sur.get_width()  + (int(view.get_x_offset()) % sur.get_width()),
               y * sur.get_height() + (int(view.get_y_offset()) % sur.get_height()));
}

/* EOF */
