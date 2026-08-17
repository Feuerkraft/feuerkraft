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

#include <cmath>
#include <iostream>
#include "display.hpp"
#include "view.hpp"
#include "background.hpp"

Background::Background (const Sprite& arg_sprite,
                        float arg_z_pos)
  : sprite(arg_sprite),
    z_pos(arg_z_pos)
{
  sprite.set_alignment(origin_top_left);
  if (sprite.get_width() <= 0 || sprite.get_height() <= 0)
    {
      std::cerr << "Background: sand sprite has no frames "
                << "(width=" << sprite.get_width()
                << " height=" << sprite.get_height() << ")\n";
    }
}

void
Background::draw (View& view)
{
  float left, top, right, bottom;
  view.get_world_rect(left, top, right, bottom);

  // Always paint a solid desert base so empty map cells are never pure black
  // (also covers the case where the sand texture failed to load).
  // z below tiles (-5) and matching the sand sprites so nothing covers it
  view.get_sc().color().draw_fillrect(left, top, right, bottom,
                                       Color(194, 178, 128),
                                       z_pos - 0.1f);

  int sw = sprite.get_width();
  int sh = sprite.get_height();
  if (sw <= 0 || sh <= 0)
    return;

  // Expand by one tile so scrolling never shows gaps.
  int x0 = int(std::floor(left  / float(sw))) - 1;
  int y0 = int(std::floor(top   / float(sh))) - 1;
  int x1 = int(std::ceil (right / float(sw))) + 1;
  int y1 = int(std::ceil (bottom/ float(sh))) + 1;

  for (int y = y0; y <= y1; ++y)
    for (int x = x0; x <= x1; ++x)
      {
        view.get_sc().color().draw(sprite,
                                   float(x * sw),
                                   float(y * sh),
                                   z_pos);
      }
}

/* EOF */
