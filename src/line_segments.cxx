//  $Id: line_segments.cxx,v 1.1 2003/05/04 09:31:49 grumbel Exp $
//
//  Pingus - A free Lemmings clone
//  Copyright (C) 2002 Ingo Ruhnke <grumbel@gmx.de>
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

#include <math.h>
#include <assert.h>
#include "line_segments.hxx"

float
LineSegments::calc_length(const Segment& segment)
{
  switch(segment.type)
    {
    case STRAIGHT:
      return 0;
    case RADIAL:
      float xlen = segment.straight.x2 - segment.straight.x1;
      float ylen = segment.straight.y2 - segment.straight.y1;
      return sqrt(xlen*xlen + ylen*ylen);
    }
  return 0;
}

LineSegments::Segments::iterator
LineSegments::get_segment(float l)
{
  float len = 0.0f;
  
  Segments::iterator seg = segments.end();
  for(Segments::iterator i = segments.begin(); i != segments.end(); ++i)
    {
      if (len < l)
        seg = i;
      else
        return seg;
    }
  return seg;
}

CL_Vector
LineSegments::get_pos(float l)
{
  float len = 0.0f;
  
  Segments::iterator seg = segments.end();
  for(Segments::iterator i = segments.begin(); i != segments.end(); ++i)
    {
      if (len < l)
        seg = i;
      else
        break;
    }

  assert(seg != segments.end());
  
  return get_pos(*seg, seg->length - (len - l));
}

float
LineSegments::get_length()
{
  float len = 0.0f;

  for(Segments::iterator i = segments.begin(); i != segments.end(); ++i)
    len += i->length;
  
  return len;
}

CL_Vector
LineSegments::get_pos(const Segment& segment, float len)
{
  switch(segment.type)
    {
    case STRAIGHT:
      return CL_Vector();
    case RADIAL:
      {
        // relative position on the segment
        float rel_pos = calc_length(segment);
        float xlen = segment.straight.x2 - segment.straight.x1;
        float ylen = segment.straight.y2 - segment.straight.y1;

        return CL_Vector(segment.straight.x1 + (xlen * rel_pos),
                         segment.straight.y1 + (ylen * rel_pos));
      }
    }
  return CL_Vector();
}

void
LineSegments::add_straight_segment(float x1, float y1, float x2, float y2)
{
  Segment segment;

  segment.straight.x1 = x1;
  segment.straight.y1 = y1;
  segment.straight.x2 = x2;
  segment.straight.y2 = y2;


  segment.type   = STRAIGHT;
  segment.length = calc_length(segment);

  segments.push_back(segment);
}

void
LineSegments::add_radial_segment(float x, float y, float radius, float start_angle, float stop_angle)
{
  Segment segment;

  segment.radial.x = x;
  segment.radial.y = y;
  segment.radial.radius = radius;
  segment.radial.start_angle = start_angle;
  segment.radial.end_angle  = stop_angle;

  segment.type   = RADIAL;
  segment.length = calc_length(segment);

  segments.push_back(segment);
}

/* EOF */
