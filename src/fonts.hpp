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

#ifndef HEADER_FEUERKRAFT_FONTS_HXX
#define HEADER_FEUERKRAFT_FONTS_HXX

#include <string>
#include "sprite.hpp"

/** Minimal font stub used during the SDL2 port.
 *  Provides the methods call sites expect; rendering is a no-op until
 *  a real bitmap/TTF implementation is added. */
class Font
{
public:
  Font() {}

  int get_height() const { return 12; }
  int get_width(const std::string& text) const { return static_cast<int>(text.size()) * 7; }

  struct BoundingRect {
    int width, height;
    int get_width() const { return width; }
    int get_height() const { return height; }
  };

  BoundingRect bounding_rect(int /*x*/, int /*y*/, const std::string& text) const {
    BoundingRect b;
    b.width = get_width(text);
    b.height = get_height();
    return b;
  }

  void set_alignment(Origin /*o*/) {}
  void set_alpha(float /*a*/) {}
  void draw(int /*x*/, int /*y*/, const std::string& /*text*/) {}
};

namespace Fonts {

extern Font font;

void init();
void deinit();

} // namespace Fonts

#endif

/* EOF */
