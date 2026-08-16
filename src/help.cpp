// Feuerkraft - A Tank Battle Game
// Copyright (C) 2002 Ingo Ruhnke <grumbel@gmail.com>
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

#include "fonts.hpp"
#include "help.hpp"

Help::Help()
{
  font = Fonts::font;
}

Help::~Help()
{
}

void
Help::draw(SDL_Renderer* gc)
{
  int center_x = Display::get_width()/2;
  int center_y = Display::get_height()/2;

  Display::fill_rect(Rect(center_x - 200, center_y - 150,
                                center_x + 200, center_y + 150),
                        Color(100, 100, 0, 230));
  font.set_alignment(origin_top_left);
  font.draw(center_x - 190, center_y - 120,
            "F1 - show/hide this help screen\n"
            "Esc - leave game\n"
            "j  - enter/leave a vehicle\n"
            "left - turn left\n"
            "right - turn right\n"
            );
}

void
Help::update(float delta)
{
}

/* EOF */
