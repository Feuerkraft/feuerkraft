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

#include "color.hpp"

Color::Color()
  : red(1.0f), green(1.0f), blue(1.0f), alpha(1.0f)
{
}

Color::Color(float red_, float green_, float blue_, float alpha_)
  : red(red_), green(green_), blue(blue_), alpha(alpha_)
{
}

Color::Color(int r, int g, int b, int a)
  : red(r / 255.0f), green(g / 255.0f), blue(b / 255.0f), alpha(a / 255.0f)
{
}

SDL_Color
Color::to_sdl() const
{
  SDL_Color c;
  c.r = static_cast<Uint8>(red   * 255.0f);
  c.g = static_cast<Uint8>(green * 255.0f);
  c.b = static_cast<Uint8>(blue  * 255.0f);
  c.a = static_cast<Uint8>(alpha * 255.0f);
  return c;
}

/* EOF */
