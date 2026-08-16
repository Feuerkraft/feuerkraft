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

#include <algorithm>
#include <cmath>
#include <cassert>
#include "drawing_context.hpp"
#include "display.hpp"
#include "sprite.hpp"

struct DrawingRequestsSorter
{
  bool operator()(DrawingRequest* a, DrawingRequest* b) {
    return a->get_z_pos() < b->get_z_pos();
  }
};

class FillScreenDrawingRequest : public DrawingRequest
{
private:
  Color color;
public:
  FillScreenDrawingRequest(const Color& color_)
    : DrawingRequest(Vector3f(0, 0, -1000.0f)), color(color_)
  {
  }
  virtual ~FillScreenDrawingRequest() {}

  void draw(SDL_Renderer* renderer) {
    SDL_Color c = color.to_sdl();
    SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_RenderClear(renderer);
  }
};

class LineDrawingRequest : public DrawingRequest
{
  float x1, y1, x2, y2;
  Color color;
public:
  LineDrawingRequest(float x1_, float y1_, float x2_, float y2_,
                     const Color& color_, float z)
    : DrawingRequest(Vector3f(x1_, y1_, z)),
      x1(x1_), y1(y1_), x2(x2_), y2(y2_), color(color_)
  {}

  void draw(SDL_Renderer* renderer) {
    SDL_Color c = color.to_sdl();
    SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_RenderDrawLine(renderer,
                       static_cast<int>(x1), static_cast<int>(y1),
                       static_cast<int>(x2), static_cast<int>(y2));
  }
};

class FillRectDrawingRequest : public DrawingRequest
{
  float x1, y1, x2, y2;
  Color color;
public:
  FillRectDrawingRequest(float x1_, float y1_, float x2_, float y2_,
                         const Color& color_, float z)
    : DrawingRequest(Vector3f(x1_, y1_, z)),
      x1(x1_), y1(y1_), x2(x2_), y2(y2_), color(color_)
  {}

  void draw(SDL_Renderer* renderer) {
    SDL_Color c = color.to_sdl();
    SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_Rect r;
    r.x = static_cast<int>(std::min(x1, x2));
    r.y = static_cast<int>(std::min(y1, y2));
    r.w = static_cast<int>(std::fabs(x2 - x1));
    r.h = static_cast<int>(std::fabs(y2 - y1));
    SDL_RenderFillRect(renderer, &r);
  }
};

class RectDrawingRequest : public DrawingRequest
{
  float x1, y1, x2, y2;
  Color color;
public:
  RectDrawingRequest(float x1_, float y1_, float x2_, float y2_,
                     const Color& color_, float z)
    : DrawingRequest(Vector3f(x1_, y1_, z)),
      x1(x1_), y1(y1_), x2(x2_), y2(y2_), color(color_)
  {}

  void draw(SDL_Renderer* renderer) {
    SDL_Color c = color.to_sdl();
    SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_Rect r;
    r.x = static_cast<int>(std::min(x1, x2));
    r.y = static_cast<int>(std::min(y1, y2));
    r.w = static_cast<int>(std::fabs(x2 - x1));
    r.h = static_cast<int>(std::fabs(y2 - y1));
    SDL_RenderDrawRect(renderer, &r);
  }
};


class SpriteDrawingRequest : public DrawingRequest
{
  Sprite sprite;
public:
  SpriteDrawingRequest(const Sprite& sprite_, const Vector3f& pos_)
    : DrawingRequest(pos_), sprite(sprite_)
  {}
  void draw(SDL_Renderer* /*renderer*/) {
    sprite.draw(pos.x, pos.y);
  }
};

class TextDrawingRequest : public DrawingRequest
{
  std::string text;
public:
  TextDrawingRequest(const std::string& text_, const Vector3f& pos_)
    : DrawingRequest(pos_), text(text_)
  {}
  virtual ~TextDrawingRequest() {}

  void draw(SDL_Renderer* /*renderer*/) {
    // Font rendering will be implemented with the font port
  }
};

DrawingContext::DrawingContext()
{
  translate_stack.push_back(Pointf(0, 0));
}

void
DrawingContext::render(SDL_Renderer* renderer)
{
  std::stable_sort(drawingrequests.begin(), drawingrequests.end(), DrawingRequestsSorter());

  for (DrawingRequests::iterator i = drawingrequests.begin(); i != drawingrequests.end(); ++i)
    {
      (*i)->draw(renderer);
    }
}

void
DrawingContext::clear()
{
  for (DrawingRequests::iterator i = drawingrequests.begin(); i != drawingrequests.end(); ++i)
    {
      delete *i;
    }
  drawingrequests.clear();
}

void
DrawingContext::draw(DrawingRequest* request)
{
  drawingrequests.push_back(request);
}


void
DrawingContext::draw(const Sprite& sprite, float x, float y, float z)
{
  draw(new SpriteDrawingRequest(sprite,
        Vector3f(translate_stack.back().x + x,
                 translate_stack.back().y + y, z)));
}

void
DrawingContext::draw(const std::string& text, float x, float y, float z)
{
  draw(new TextDrawingRequest(text, Vector3f(translate_stack.back().x + x,
                                             translate_stack.back().y + y,
                                             z)));
}

void
DrawingContext::draw_line(float x1, float y1, float x2, float y2,
                          const Color& color)
{
  float tx = translate_stack.back().x;
  float ty = translate_stack.back().y;
  draw(new LineDrawingRequest(tx + x1, ty + y1, tx + x2, ty + y2, color, 0));
}

void
DrawingContext::draw_fillrect(float x1, float y1, float x2, float y2,
                              const Color& color)
{
  float tx = translate_stack.back().x;
  float ty = translate_stack.back().y;
  draw(new FillRectDrawingRequest(tx + x1, ty + y1, tx + x2, ty + y2, color, 0));
}

void
DrawingContext::draw_rect(float x1, float y1, float x2, float y2,
                          const Color& color)
{
  float tx = translate_stack.back().x;
  float ty = translate_stack.back().y;
  draw(new RectDrawingRequest(tx + x1, ty + y1, tx + x2, ty + y2, color, 0));
}

void
DrawingContext::draw_pixel(float x_pos, float y_pos, const Color& color)
{
  draw_fillrect(x_pos, y_pos, x_pos + 1, y_pos + 1, color);
}

void
DrawingContext::draw_circle(float x_pos, float y_pos, float radius,
                            const Color& color)
{
  // Approximate with a regular polygon
  const int steps = 32;
  float tx = translate_stack.back().x + x_pos;
  float ty = translate_stack.back().y + y_pos;
  float last_x = tx + radius;
  float last_y = ty;
  for (int i = 1; i <= steps; ++i)
    {
      float a = (2.0f * static_cast<float>(M_PI) * i) / steps;
      float x = tx + radius * std::cos(a);
      float y = ty + radius * std::sin(a);
      draw(new LineDrawingRequest(last_x, last_y, x, y, color, 0));
      last_x = x;
      last_y = y;
    }
}

void
DrawingContext::draw_arc(float x_pos, float y_pos, float radius,
                         float angle_start, float angle_end,
                         const Color& color)
{
  const int steps = 16;
  float enclosed = angle_end - angle_start;
  float tx = translate_stack.back().x + x_pos;
  float ty = translate_stack.back().y + y_pos;
  float last_x = tx + radius * std::cos(angle_start);
  float last_y = ty + radius * std::sin(angle_start);
  for (int i = 1; i <= steps; ++i)
    {
      float a = angle_start + enclosed * i / steps;
      float x = tx + radius * std::cos(a);
      float y = ty + radius * std::sin(a);
      draw(new LineDrawingRequest(last_x, last_y, x, y, color, 0));
      last_x = x;
      last_y = y;
    }
}

void
DrawingContext::fill_screen(const Color& color)
{
  draw(new FillScreenDrawingRequest(color));
}

void
DrawingContext::rotate(float /*angel*/)
{
  // not implemented yet
}

void
DrawingContext::scale(float /*x*/, float /*y*/)
{
  // not implemented yet
}

void
DrawingContext::translate(float x, float y)
{
  translate_stack.back().x += x;
  translate_stack.back().y += y;
}

void
DrawingContext::push_modelview()
{
  translate_stack.push_back(translate_stack.back());
}

void
DrawingContext::pop_modelview()
{
  translate_stack.pop_back();
  assert(!translate_stack.empty());
}

void
DrawingContext::reset_modelview()
{
  translate_stack.clear();
  translate_stack.push_back(Pointf(0, 0));
}

Rect
DrawingContext::get_clip_rect()
{
  return Rect(Pointf(translate_stack.back().x, translate_stack.back().y),
              Display::get_width(), Display::get_height());
}

/* EOF */
