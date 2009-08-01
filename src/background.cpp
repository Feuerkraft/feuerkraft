//  $Id: background.cpp,v 1.14 2003/10/20 21:30:09 grumbel Exp $
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

#include <ClanLib/Display/display.h>
#include "view.hpp"
#include "background.hpp"

Background::Background (const CL_Sprite& arg_sprite,
                        float arg_z_pos)
  : sprite(arg_sprite),
    z_pos(arg_z_pos)
{
  sprite.set_alignment(origin_top_left);
}

void
Background::draw (View& view)
{
  //sprite.draw();
  // FIXME: We should take the view size and surface size into account
  for (int y = -1; y <= 2; ++y)
    for (int x = -1; x <= 2; ++x)
      sprite.draw(x * sprite.get_width()  + (int(view.get_x_offset()) % sprite.get_width()),
                  y * sprite.get_height() + (int(view.get_y_offset()) % sprite.get_height()));
}

/* EOF */
