//  $Id: View.cxx,v 1.11 2002/03/25 19:30:56 grumbel Exp $
//
//  Pingus - A free Lemmings clone
//  Copyright (C) 2000 Ingo Ruhnke <grumbel@gmx.de>
//
//  This program is free software; you can redistribute it and/or
//  modify it under the terms of the GNU General Public License
//  as published by the Free Software Foundation; either version 2
//  of the License, or (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program; if not, write to the Free Software
//  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

#include <ClanLib/core.h>
#include <ClanLib/display.h>
#include <SphriteLib/sphritelibGL.h>
#include "View.hxx"

View::View (boost::dummy_ptr<GameWorld> arg_world, 
	    int arg_x1, int arg_y1, 
	    int arg_x2, int arg_y2,
	    int arg_x_offset, int arg_y_offset) :
  world (arg_world), x1 (arg_x1), y1 (arg_y1), x2 (arg_x2), y2 (arg_y2),
  x_offset (-arg_x_offset), y_offset (-arg_y_offset)
{
  x_offset -= x1;
  y_offset -= y1;
  zoom = 1.0;
  rotation = 0;
}

View::~View ()
{
}

void 
View::update (float delta)
{
  // nothing to do
}

void 
View::draw ()
{
  CL_Display::push_clip_rect (CL_ClipRect (x1, y1, x2, y2));
  /*glPushMatrix ();
  glTranslated (400, 300, 0.0);
  glScaled (zoom, zoom, 1.0);
  glRotated (rotation, 0, 0, 1.0);
  glTranslated (-400, -300, 0.0);*/
  
  world->draw (this);
  world->draw_energie (this);

  //glPopMatrix ();

  CL_Display::pop_clip_rect ();
}

int View::get_x_offset () { return x1 - x_offset + (x2 - x1)/2; }
int View::get_y_offset () { return y1 - y_offset + (y2 - y1)/2; }
int View::get_x1 () { return x1; }
int View::get_x2 () { return x2; }
int View::get_y1 () { return y1; }
int View::get_y2 () { return y2; }

void 
View::set_view (int x_pos, int y_pos)
{
  x_offset = x_pos;
  y_offset = y_pos;
}

void 
View::set_zoom (float z)
{
  zoom = z;
}

void 
View::draw (CL_Surface& sur, const CL_Vector& pos)
{
  sur.put_screen (int(pos.x + get_x_offset ()),
		  int(pos.y + get_y_offset ()));
}

void
View::draw (Sprite& sprite, const CL_Vector& pos, float angle)
{
  draw (&sprite, pos, angle);
}

void 
View::draw (Sprite* sprite, const CL_Vector& pos, float angle)
{
  sprite->draw(int(pos.x + get_x_offset ()), int(pos.y + get_y_offset ()),
	       angle/3.1415927 * 180.0f);
}

void 
View::draw (CL_Surface& sur, int x_pos, int y_pos)
{
  sur.put_screen (x_pos + get_x_offset (),
		  y_pos + get_y_offset ());
}

void 
View::draw (CL_Surface& sur, int x_pos, int y_pos, int frame)
{
  sur.put_screen (x_pos + get_x_offset (),
		  y_pos + get_y_offset (), frame);  
}

void 
View::draw (CL_Surface& sur, int x_pos, int y_pos, 
	    float size_x, float size_y, int frame)
{
  sur.put_screen (x_pos + get_x_offset (),
		  y_pos + get_y_offset (),
		  size_x * zoom, size_y * zoom, frame);  
}

void 
View::draw_line (int x1, int y1, int x2, int y2, 
		float r, float g, float b, float a)
{
  if (zoom == 1.0)
    {
      CL_Display::draw_line (x1 + get_x_offset (), y1 + get_y_offset (),
			     x2 + get_x_offset (), y2 + get_y_offset (),
			     r, g, b, a);
    }
  else
    {
      CL_Display::draw_line (int((x1 + get_x_offset ())),
			     int((y1 + get_y_offset ())),
			     int((x2 + get_x_offset ())),
			     int((y2 + get_y_offset ())),
			     r, g, b, a);
    }
}

void 
View::draw_fillrect (int x1, int y1, int x2, int y2, 
		    float r, float g, float b, float a)
{
  CL_Display::fill_rect (int((x1 + get_x_offset ())),
			 int((y1 + get_y_offset ())), 
			 int((x2 + get_x_offset ())),
			 int((y2 + get_y_offset ())),
			 r, g, b, a);
}

void 
View::draw_rect (int x1, int y1, int x2, int y2, 
		 float r, float g, float b, float a)
{
  CL_Display::draw_line (x1 + get_x_offset (), y1 + get_y_offset (), 
			 x1 + get_x_offset (), y2 + get_y_offset (),
			 r, g, b, a);
  CL_Display::draw_line (x2 + get_x_offset (), y1 + get_y_offset (), 
			 x2 + get_x_offset (), y2 + get_y_offset (),
			 r, g, b, a);
  CL_Display::draw_line (x1 + get_x_offset (), y1 + get_y_offset (), 
			 x2 + get_x_offset (), y1 + get_y_offset (),
			 r, g, b, a);
  CL_Display::draw_line (x1 + get_x_offset (), y2 + get_y_offset (), 
			 x2 + get_x_offset (), y2 + get_y_offset (),
			 r, g, b, a);
}

void 
View::draw_pixel (int x_pos, int y_pos, 
		   float r, float g, float b, float a)
{
  //CL_Display::put_pixel (x1 + get_x_offset (),
  //			 y1 + get_y_offset (), r, g, b, a);
  std::cout << "View::draw_pixel () not implemented" << std::endl;
}

void 
View::draw_circle (int x_pos, int y_pos, int radius,
		   float r, float g, float b, float a)
{
  // FIXME: Probally not the fast circle draw algo on this world...
  const float pi = 3.1415927f * 2.0f;
  const float steps = 8;
  CL_Vector current (radius, 0);
  CL_Vector next = current.rotate (pi/steps, CL_Vector (0, 0, 1.0f));

  for (int i = 0; i < steps; ++i)
    {
      draw_line (int(x_pos + current.x), int(y_pos + current.y),
		 int(x_pos + next.x), int(y_pos + next.y),
		 r, g, b, a);
      current = next;
      next = next.rotate (pi/8, CL_Vector (0, 0, 1.0f));
    }
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

CL_Vector
View::screen_to_world (const CL_Vector& pos)
{
  return CL_Vector (pos.x - get_x_offset (),
		    pos.y - get_y_offset ());
}

CL_Vector
View::world_to_screen (const CL_Vector& pos)
{
  return CL_Vector (pos.x + get_x_offset (),
		    pos.y + get_y_offset ());
}

/* EOF */
