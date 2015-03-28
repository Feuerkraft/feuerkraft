//  $Id$
//
//  Pingus - A free Lemmings clone
//  Copyright (C) 2002 Ingo Ruhnke <grumbel@gmx.de>
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//  
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//  
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include <assert.h>
#include <ClanLib/Display/sprite.h>
#include <ClanLib/Display/graphic_context.h>
#include <iostream>
#include "drawing_context.hpp"

struct DrawingRequestsSorter
{
  bool operator()(DrawingRequest* a, DrawingRequest* b) {
    return a->get_z_pos() < b->get_z_pos();
  }
};

class FillScreenDrawingRequest : public DrawingRequest
{
private:
  CL_Color color;
public:
  FillScreenDrawingRequest(const CL_Color& color_) 
    : DrawingRequest(CL_Vector(0, 0, -1000.0f)), color(color_)
  {
  }
  virtual ~FillScreenDrawingRequest() {}

  void draw(CL_GraphicContext* gc) {
    gc->clear(color);
  }
};

class SpriteDrawingRequest : public DrawingRequest
{
private:
  CL_Sprite sprite;

public:
  SpriteDrawingRequest(const CL_Sprite& sprite_, const CL_Vector& pos_)
    : DrawingRequest(pos_),
      sprite(sprite_)
  {}
  virtual ~SpriteDrawingRequest() {}

  void draw(CL_GraphicContext* gc) {
    sprite.draw(static_cast<int>(pos.x), static_cast<int>(pos.y), gc);
  }
};

class TextDrawingRequest : public DrawingRequest
{
private:
  std::string text;
public:
  TextDrawingRequest(const std::string& text_, const CL_Vector& pos_)
    : DrawingRequest(pos_),
      text(text_)
  {}
  virtual ~TextDrawingRequest() {}

  void draw(CL_GraphicContext* gc) {
    // FIXME: not implemented
  }
};

DrawingContext::DrawingContext()
{
  translate_stack.push_back(CL_Pointf(0, 0));
}

void
DrawingContext::render(CL_GraphicContext* gc)
{
  std::stable_sort(drawingrequests.begin(), drawingrequests.end(), DrawingRequestsSorter());
  
  for(DrawingRequests::iterator i = drawingrequests.begin(); i != drawingrequests.end(); ++i)
    {
      (*i)->draw(gc);
    }
}

void
DrawingContext::clear()
{
  for(DrawingRequests::iterator i = drawingrequests.begin(); i != drawingrequests.end(); ++i)
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
DrawingContext::draw(const CL_Sprite&   sprite,  float x, float y, float z)
{ // FIXME: This should get flattend down to a simple texture draw
  // command for easier sorting after texture-id/alpha
  draw(new SpriteDrawingRequest(sprite, CL_Vector(translate_stack.back().x + x,
                                                  translate_stack.back().y + y,
                                                  z)));
}

void
DrawingContext::draw(const std::string& text,    float x, float y, float z)
{ 
  draw(new TextDrawingRequest(text, CL_Vector(x, y, z)));
}

void
DrawingContext::draw_line (float x1, float y1, float x2, float y2, 
                           const CL_Color& color)
{
}

void
DrawingContext::draw_fillrect (float x1, float y1, float x2, float y2, 
		      const CL_Color& color)
{
}

void
DrawingContext::draw_rect (float x1, float y1, float x2, float y2, 
		  const CL_Color& color)
{
}

void
DrawingContext::draw_pixel (float x_pos, float y_pos, 
		   const CL_Color& color)
{
}

void
DrawingContext::draw_circle (float x_pos, float y_pos, float radius,
                             const CL_Color& color)
{
}

/** Draws an arc, starting from angle_start to angle_end in
      counterclockwise direction. Angles are taken in radian */
void
DrawingContext::draw_arc (float x_pos, float y_pos, float radius, float angle_start, float angle_end,
                          const CL_Color& color)
{
}

void
DrawingContext::fill_screen(const CL_Color& color)
{
  draw(new FillScreenDrawingRequest(color));
}

void
DrawingContext::rotate(float angel)
{
  // FIXME: not implemented
}

void
DrawingContext::scale(float x, float y)
{
  // FIXME: not implemented
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
  translate_stack.push_back(CL_Pointf(0, 0));
}

CL_Rect
DrawingContext::get_clip_rect()
{
  return CL_Rect(CL_Point(static_cast<int>(translate_stack.back().x),
                          static_cast<int>(translate_stack.back().y)),
                 CL_Size(800, 600));
}

/* EOF */
