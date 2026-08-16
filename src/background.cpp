// Feuerkraft - A Tank Battle Game
// Copyright (C) 2000 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include "view.hpp"
#include "background.hpp"

Background::Background (const Sprite& arg_sprite,
                        float arg_z_pos)
  : sprite(arg_sprite),
    z_pos(arg_z_pos)
{
  sprite.set_alignment(origin_top_left);
}

void
Background::draw (View& view)
{
  // Tile the background in screen space, but queue through the color
  // DrawingContext so it ends up on the lightmap color buffer (direct
  // sprite.draw() would hit the window and be overwritten by SceneContext).
  int sw = sprite.get_width();
  int sh = sprite.get_height();
  if (sw <= 0 || sh <= 0)
    return;

  float ox = view.get_x_offset();
  float oy = view.get_y_offset();

  // SceneContext applies translate(ox, oy); pass world coords so that
  // world + translate = screen position.
  int mod_x = int(ox) % sw;
  int mod_y = int(oy) % sh;
  // C++ % can be negative for negative offsets
  if (mod_x < 0) mod_x += sw;
  if (mod_y < 0) mod_y += sh;

  for (int y = -1; y <= 2; ++y)
    for (int x = -1; x <= 2; ++x)
      {
        float screen_x = float(x * sw + mod_x);
        float screen_y = float(y * sh + mod_y);
        view.get_sc().color().draw(sprite,
                                   screen_x - ox,
                                   screen_y - oy,
                                   z_pos);
      }
}

/* EOF */
