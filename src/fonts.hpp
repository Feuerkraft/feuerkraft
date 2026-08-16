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
#include <map>
#include <vector>
#include <SDL.h>
#include "sprite.hpp"

/** Bitmap font built from a horizontal glyph strip (ClanLib-style). */
class Font
{
public:
  struct Glyph {
    int x, y, w, h;
  };

  struct BoundingRect {
    int width, height;
    int get_width() const { return width; }
    int get_height() const { return height; }
  };

private:
  SDL_Texture* texture;
  int texture_w;
  int texture_h;
  int line_height;
  int space_width;
  std::map<char, Glyph> glyphs;
  Origin alignment;
  float alpha;

public:
  Font();
  ~Font();

  /** Load a horizontal glyph atlas. Glyphs are detected by opaque
   *  pixel runs; `letters` maps them left-to-right to characters. */
  bool load(const std::string& image_path, const std::string& letters);

  int get_height() const { return line_height; }
  int get_width(const std::string& text) const;

  BoundingRect bounding_rect(int /*x*/, int /*y*/, const std::string& text) const {
    BoundingRect b;
    b.width = get_width(text);
    b.height = get_height();
    return b;
  }

  void set_alignment(Origin o) { alignment = o; }
  void set_alpha(float a) { alpha = a; }

  void draw(int x, int y, const std::string& text) const;

private:
  Font(const Font&);
  Font& operator=(const Font&);
};

namespace Fonts {

extern Font font;

void init();
void deinit();

} // namespace Fonts

#endif

/* EOF */
