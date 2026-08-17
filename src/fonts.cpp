// Feuerkraft - A Tank Battle Game
#include <algorithm>
#include <vector>
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

#include <iostream>
#include <SDL_image.h>
#include "fonts.hpp"
#include "display.hpp"
#include "path_manager.hpp"

Font::Font()
  : texture(nullptr), texture_w(0), texture_h(0),
    line_height(12), space_width(4),
    alignment(origin_top_left), alpha(1.0f)
{
}

Font::~Font()
{
  if (texture)
    {
      SDL_DestroyTexture(texture);
      texture = nullptr;
    }
}

bool
Font::load(const std::string& image_path, const std::string& letters)
{
  if (texture)
    {
      SDL_DestroyTexture(texture);
      texture = nullptr;
    }
  glyphs.clear();

  SDL_Surface* surface = IMG_Load(image_path.c_str());
  if (!surface)
    {
      std::cerr << "Font: failed to load " << image_path
                << ": " << IMG_GetError() << std::endl;
      return false;
    }

  SDL_Renderer* renderer = Display::get_renderer();
  if (!renderer)
    {
      std::cerr << "Font: no renderer when loading " << image_path << std::endl;
      SDL_FreeSurface(surface);
      return false;
    }

  texture_w = surface->w;
  texture_h = surface->h;
  line_height = surface->h;

  // Convert for easy pixel access
  SDL_Surface* rgba = SDL_ConvertSurfaceFormat(surface, SDL_PIXELFORMAT_RGBA32, 0);
  SDL_FreeSurface(surface);
  if (!rgba)
    {
      std::cerr << "Font: convert failed: " << SDL_GetError() << std::endl;
      return false;
    }

  SDL_LockSurface(rgba);
  auto pixel_alpha = [&](int x, int y) -> Uint8 {
    Uint32* p = reinterpret_cast<Uint32*>(
      static_cast<Uint8*>(rgba->pixels) + y * rgba->pitch + x * 4);
    Uint8 r, g, b, a;
    SDL_GetRGBA(*p, rgba->format, &r, &g, &b, &a);
    return a;
  };

  auto col_empty = [&](int x) {
    for (int y = 0; y < rgba->h; ++y)
      if (pixel_alpha(x, y) > 0)
        return false;
    return true;
  };

  std::vector<Glyph> regions;
  int x = 0;
  while (x < rgba->w)
    {
      while (x < rgba->w && col_empty(x))
        ++x;
      if (x >= rgba->w)
        break;
      int start = x;
      while (x < rgba->w && !col_empty(x))
        ++x;
      Glyph g;
      g.x = start;
      g.y = 0;
      g.w = x - start;
      g.h = rgba->h;
      regions.push_back(g);
    }
  SDL_UnlockSurface(rgba);

  texture = SDL_CreateTextureFromSurface(renderer, rgba);
  SDL_FreeSurface(rgba);
  if (!texture)
    {
      std::cerr << "Font: CreateTexture failed: " << SDL_GetError() << std::endl;
      return false;
    }
  SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
  #if SDL_VERSION_ATLEAST(2, 0, 12)
  SDL_SetTextureScaleMode(texture, SDL_ScaleModeLinear);
  #endif

  if (regions.size() != letters.size())
    {
      std::cerr << "Font: glyph count " << regions.size()
                << " != letters " << letters.size()
                << " for " << image_path << std::endl;
    }

  size_t n = std::min(regions.size(), letters.size());
  for (size_t i = 0; i < n; ++i)
    glyphs[letters[i]] = regions[i];

  // Space width: half of typical glyph or 'n' width
  if (glyphs.count('n'))
    space_width = std::max(3, glyphs['n'].w / 2);
  else if (!regions.empty())
    space_width = std::max(3, regions[0].w / 2);

  std::cout << "Font: loaded " << glyphs.size() << " glyphs from "
            << image_path << std::endl;
  return true;
}

int
Font::get_width(const std::string& text) const
{
  int w = 0;
  for (size_t i = 0; i < text.size(); ++i)
    {
      char c = text[i];
      if (c == '\n')
        continue;
      if (c == ' ')
        {
          w += space_width;
          continue;
        }
      auto it = glyphs.find(c);
      if (it != glyphs.end())
        w += it->second.w + 1; // 1px kerning gap
      else
        w += space_width;
    }
  return w;
}

void
Font::draw(int x, int y, const std::string& text) const
{
  if (!texture)
    return;
  SDL_Renderer* renderer = Display::get_renderer();
  if (!renderer)
    return;

  SDL_SetTextureAlphaMod(texture, static_cast<Uint8>(alpha * 255.0f));

  // Multi-line support
  std::vector<std::string> lines;
  {
    std::string cur;
    for (char c : text)
      {
        if (c == '\n')
          {
            lines.push_back(cur);
            cur.clear();
          }
        else
          cur.push_back(c);
      }
    lines.push_back(cur);
  }

  int line_y = y;
  for (const std::string& line : lines)
    {
      int line_w = get_width(line);
      int draw_x = x;
      if (alignment == origin_top_center || alignment == origin_center)
        draw_x = x - line_w / 2;
      else if (alignment == origin_top_left)
        draw_x = x;

      int cx = draw_x;
      for (char c : line)
        {
          if (c == ' ')
            {
              cx += space_width;
              continue;
            }
          auto it = glyphs.find(c);
          if (it == glyphs.end())
            {
              cx += space_width;
              continue;
            }
          const Glyph& g = it->second;
          SDL_Rect src = { g.x, g.y, g.w, g.h };
          SDL_Rect dst = { cx, line_y, g.w, g.h };
          SDL_RenderCopy(renderer, texture, &src, &dst);
          cx += g.w + 1;
        }
      line_y += line_height + 2;
    }
}

namespace Fonts {

Font font;

void init()
{
  // From data/feuerkraft.xml:
  // <bitmap glyphs="font_glyphs" letters="!_#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_`abcdefghijklmnopqrstuvwxyz{|}~" />
  const char* letters =
    "!_#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_"
    "`abcdefghijklmnopqrstuvwxyz{|}~";
  // Note: in the XML the 2nd character is '_' standing in for '\"' or space-adjacent;
  // the strip maps left-to-right to this string. The original ClanLib letter list
  // used '\"' which we represent as position 1 = '_' in the resource file as written.

  std::string path = path_manager.complete("images/verdana11.png");
  if (!font.load(path, letters))
    std::cerr << "Fonts::init: bitmap font failed to load" << std::endl;
}

void deinit()
{
  // Font destructor frees texture when static object is destroyed;
  // nothing extra required here for the single global font.
}

} // namespace Fonts

/* EOF */
