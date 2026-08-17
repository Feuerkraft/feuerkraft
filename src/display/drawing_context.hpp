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

#ifndef HEADER_DRAWING_CONTEXT_HXX
#define HEADER_DRAWING_CONTEXT_HXX

#include <vector>
#include <string>
#include <SDL.h>
#include "drawing_request.hpp"
#include "math_types.hpp"
#include "color.hpp"

// Forward declaration; full Sprite type comes later in the port
class Sprite;

/** The DrawingContext collects all DrawingRequests and allows you to
    flush them all down to the graphics card in one run, this has the
    advantage that it is possible to z-sort, texture-id sort or
    otherwise optimize the drawing. In addition to that it also allows
    you do render the drawing commands to multiple buffers which might
    be usefull for post-processing effects and such. */
class DrawingContext
{
private:
  typedef std::vector<DrawingRequest*> DrawingRequests;
  DrawingRequests drawingrequests;

  struct Transform {
    float x, y;   // translation
    float sx, sy; // scale
    Transform() : x(0), y(0), sx(1), sy(1) {}
  };
  std::vector<Transform> transform_stack;

  /** Apply current transform to a point. */
  void transform(float& x, float& y) const;

public:
  DrawingContext();

  /** Draws everything in the drawing context to the renderer */
  void render(SDL_Renderer* renderer);

  /** Empties the drawing context */
  void clear();

  /** Fills the screen with a given color, this is different from
      clear() in that it doesn't remove other DrawingRequest from the
      queue */
  void fill_screen(const Color& color);

  void draw(DrawingRequest* request);
  void draw(const Sprite& sprite, float x, float y, float z = 0);
  void draw(const std::string& text, float x, float y, float z = 0);

  void draw_line (float x1, float y1, float x2, float y2,
                  const Color& color);
  void draw_fillrect (float x1, float y1, float x2, float y2,
                      const Color& color);
  void draw_rect (float x1, float y1, float x2, float y2,
                  const Color& color);
  void draw_pixel (float x_pos, float y_pos,
                   const Color& color);
  void draw_circle (float x_pos, float y_pos, float radius,
                    const Color& color);

  /** Draws an arc, starting from angle_start to angle_end in
      counterclockwise direction. Angles are taken in radian */
  void draw_arc (float x_pos, float y_pos, float radius,
                 float angle_start, float angle_end,
                 const Color& color);

  void translate(float x, float y);
  void push_modelview();
  void pop_modelview();
  void reset_modelview();

  void rotate(float angel);
  void scale(float x, float y);

  /** Return the area of the screen that will be visible */
  Rect get_clip_rect();

private:
  DrawingContext (const DrawingContext&);
  DrawingContext& operator= (const DrawingContext&);
};

#endif

/* EOF */
