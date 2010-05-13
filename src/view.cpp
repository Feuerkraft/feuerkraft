//  $Id: view.cpp,v 1.19 2003/10/20 21:30:09 grumbel Exp $
//
//  Feuerkraft - A Tank Battle Game
//  Copyright (C) 2000 Ingo Ruhnke <grumbel@gmx.de>
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

#include <iostream>
#include <ClanLib/Display/display.h>
#include <ClanLib/Display/sprite.h>
#include <ClanLib/Display/surface.h>

#include "assert.hpp"
#include "color.hpp"
#include "math.hpp"
#include "view.hpp"

View* View::current_ = 0;

View::View (int arg_x1, int arg_y1, 
	    int arg_x2, int arg_y2,
	    ViewUpdater* arg_updater) :
  x1 (arg_x1), y1 (arg_y1),
  x2 (arg_x2), y2 (arg_y2),
  state(),
  view_updater(arg_updater),
  properties(),
  scene_context()
{
  //std::cout << "View: " << x1 << " " << y1 << " " << x2 << " " << y2 
    //<< " " << state.x_offset << " " << state.y_offset << std::endl;
  
  state.x_offset = -x1;
  state.y_offset = -y1;

  state.zoom = 1.0;
  state.rotation = 0;
  
  scene_context = new SceneContext();

  current_ = this;
}

View::~View ()
{
  delete view_updater;
}

float
View::get_x_offset () 
{
  return x1 - state.x_offset + (x2 - x1)/2; 
}

float
View::get_y_offset ()
{
  return y1 - state.y_offset + (y2 - y1)/2; 
}

/*
void
View::draw (CL_Sprite& sprite, const FloatVector2d& pos, float angle)
{
  sprite.set_angle(Math::rad2deg(angle));
  sprite.draw(int(pos.x + get_x_offset ()), 
              int(pos.y + get_y_offset ()));
}

void 
View::draw_line (float x1, float y1, float x2, float y2, 
                 const Color& color)
{
  CL_Display::draw_line(int((x1 + get_x_offset ())),
                        int((y1 + get_y_offset ())),
                        int((x2 + get_x_offset ())),
                        int((y2 + get_y_offset ())),
                        color.get_cl_color());
}

void 
View::draw_fillrect (float x1, float y1, float x2, float y2, 
                     const Color& color)
{
  CL_Display::fill_rect (CL_Rect(int((x1 + get_x_offset ())),
                                 int((y1 + get_y_offset ())), 
                                 int((x2 + get_x_offset ())),
                                 int((y2 + get_y_offset ()))),
			 color.get_cl_color());
}

void
View::draw_rect (float x1, float y1, float x2, float y2, 
		 const Color& arg_color)
{
  const CL_Color& color = arg_color.get_cl_color();

  CL_Display::draw_line (int(x1 + get_x_offset ()), int(y1 + get_y_offset ()), 
			 int(x1 + get_x_offset ()), int(y2 + get_y_offset ()),
			 color);
  CL_Display::draw_line (int(x2 + get_x_offset ()), int(y1 + get_y_offset ()), 
			 int(x2 + get_x_offset ()), int(y2 + get_y_offset ()),
			 color);
  CL_Display::draw_line (int(x1 + get_x_offset ()), int(y1 + get_y_offset ()), 
			 int(x2 + get_x_offset ()), int(y1 + get_y_offset ()),
			 color);
  CL_Display::draw_line (int(x1 + get_x_offset ()), int(y2 + get_y_offset ()), 
			 int(x2 + get_x_offset ()), int(y2 + get_y_offset ()),
			 color);
}

void 
View::draw_pixel (float x_pos, float y_pos, 
                  const Color& color)
{
  //CL_Display::put_pixel (x1 + get_x_offset (),
  //			 y1 + get_y_offset (), r, g, b, a);
  AssertMsg(0, "View::draw_pixel () not implemented");
}

void 
View::draw_circle (float x_pos, float y_pos, float radius,
		   const Color& color)
{
  // FIXME: Probally not the fast circle draw algo on this world...
  const float pi = 3.1415927f * 2.0f;
  const float steps = 16;
  FloatVector2d next    = FloatVector2d::make_polar(radius, 0 * pi/float(steps));

  for (int i = 1; i <= steps; ++i)
    {
      FloatVector2d current = next;
      next = FloatVector2d::make_polar(radius, i * pi/float(steps));
      
     .get_sc().color().draw_line(x_pos + current.x, y_pos + current.y,
                         x_pos + next.x,    y_pos + next.y,
                         color);
    }
}

void
View::draw_arc (float x_pos, float y_pos, float radius, float angle_start, float angle_stop,
                const Color& color)
{
  angle_start = Math::normalize_angle(angle_start);
  angle_stop  = Math::normalize_angle(angle_stop);

  const float steps = 16;

  float enclosed_angle = Math::normalize_angle(angle_stop - angle_start);
  
  float x, y;

  float last_x = x_pos + radius * cos(angle_start);
  float last_y = y_pos + radius * sin(angle_start);
  
  for(int i = 1; i <= steps; ++i)
    {
      x = x_pos + radius * cos(angle_start + i*enclosed_angle/steps);
      y = y_pos + radius * sin(angle_start + i*enclosed_angle/steps);

     .get_sc().color().draw_line(last_x, last_y, x, y, color);

      last_x = x;
      last_y = y;
    }
}
*/
void
View::set_updater(ViewUpdater* arg_updater)
{
  delete view_updater;
  view_updater = arg_updater;
}

void
View::update(float delta)
{
  //std::cout << "View:update: " << x1 << " " << y1 << " " << x2 << " " << y2 
    //<< " " << state.x_offset << " " << state.y_offset << std::endl;

  if (view_updater)
    view_updater->update(delta, state);

  scene_context->reset_modelview();
  scene_context->translate(get_x_offset(), get_y_offset());
  //drawing_context.translate(state.x_offset, state.y_offset);
}

bool
View::get_property (ViewProperty p)
{
  return properties & p;
}

void
View::set_property (ViewProperty p)
{
  properties |= p;
}

int
View::get_width ()
{
  return x2 - x1; // FIXME: Off by one?!
}

int
View::get_height ()
{
  return y2 - y1;// FIXME: Off by one?!
}

FloatVector2d
View::screen_to_world (const FloatVector2d& pos)
{
  return FloatVector2d (pos.x - get_x_offset (),
                        pos.y - get_y_offset ());
}

FloatVector2d
View::world_to_screen (const FloatVector2d& pos)
{
  return FloatVector2d (pos.x + get_x_offset (),
                        pos.y + get_y_offset ());
}

/* EOF */
