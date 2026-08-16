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

#ifndef HEADER_COLOR_HXX
#define HEADER_COLOR_HXX

#include <SDL.h>

/** Simple RGBA colour (components in 0..1 range). */
class Color
{
public:
  float red;
  float green;
  float blue;
  float alpha;

  /** Init the color to white */
  Color();

  /** Set color to the given RGBA value (0..1) */
  Color(float red_, float green_, float blue_, float alpha_ = 1.0f);

  /** Construct from 0..255 integer components */
  Color(int r, int g, int b, int a = 255);

  /** Convert to SDL_Color (0..255). */
  SDL_Color to_sdl() const;
};

#endif

/* EOF */
