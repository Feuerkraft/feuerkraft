//  $Id: line_segments.cxx,v 1.2 2003/05/04 12:12:54 grumbel Exp $
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
#include <iostream>
#include "math.hxx"
#include "view.hxx"
#include "line_segments.hxx"

LineSegments::LineSegments()
{
}

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
LineSegments::get_end_orientation()
{
  assert(segments.size() > 0);

  Segment& segment = segments.back();
  
  switch (segment.type)
    {
    case STRAIGHT:
      return atan2(segment.straight.y2 - segment.straight.y1,
                   segment.straight.x2 - segment.straight.x1);

    case RADIAL:
      
      break;
    }
  return 0;
}

CL_Vector
LineSegments::get_end_pos()
{
  assert(segments.size() > 0);

  Segment& segment = segments.back();
  switch (segment.type)
    {
    case STRAIGHT:
      return CL_Vector(segment.straight.x2,
                       segment.straight.y2);
    case RADIAL:
      break;
    }
  return CL_Vector();
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

  segment.straight.type   = STRAIGHT;
  segment.straight.length = calc_length(segment);

  segments.push_back(segment);
}

void
LineSegments::add_radial_segment(float x, float y, float radius, 
                                 float start_angle, float stop_angle, bool turn_right)
{
  Segment segment;

  segment.radial.x = x;
  segment.radial.y = y;
  segment.radial.radius = radius;
  segment.radial.start_angle = start_angle;
  segment.radial.end_angle   = stop_angle;
  segment.radial.turn_right  = turn_right;

  segment.radial.type   = RADIAL;
  segment.radial.length = calc_length(segment);

  segments.push_back(segment);
}

bool LineSegments::calc_route(float start_x, float start_y, 
                              float dest_x, float dest_y, 
                              float start_orientation, 
                              float radius, bool turn_right,
                              float& px, float& py, float& qx, float& qy,
                              float& angle_start, float& angle_final, float& length)
{
  // See AI Programming Wisdom, pp. 189
  float angle_to_p  = turn_right ? start_orientation - Math::pi_2 : start_orientation + Math::pi_2;
  px = start_x + (radius * cos(angle_to_p));
  py = start_y + (radius * sin(angle_to_p));
  float dx = dest_x - px;
  float dy = dest_y - py;
  float h  = sqrt(dx*dx + dy*dy);

  if (h < radius)
    {
      std::cout << "Couldn't generate line segment" << std::endl;
      return false;
    }

  float d = sqrt(h*h - radius*radius);
  float theta = acos(radius / h);
  
  float phi = atan2(dy, dx);

  angle_final = turn_right ? phi + theta : phi - theta;
  qx = px + radius * cos(angle_final);
  qy = py + radius * sin(angle_final);
  
  angle_start = angle_to_p + Math::pi;

  float total_curve = turn_right ? angle_start - angle_final : angle_final - angle_start;

  float curve_length = Math::normalize_angle(total_curve) * radius;

  length = d + curve_length;
  
  return true;
}

void
LineSegments::add_controll_point(float dest_x, float dest_y, float radius)
{ 
  float start_orientation = get_end_orientation();
  float start_x = get_end_pos().x;
  float start_y = get_end_pos().y;

  float l_px, l_py, l_qx, l_qy, l_angle_start, l_angle_final, l_length;
  bool  l_possible;

  l_possible = calc_route(start_x, start_y,
                          dest_x, dest_y,
                          start_orientation, radius, true,
                          l_px, l_py, l_qx, l_qy,
                          l_angle_start, l_angle_final, l_length);
  
  float r_px, r_py, r_qx, r_qy, r_angle_start, r_angle_final, r_length;
  bool r_possible;
  r_possible = calc_route(start_x, start_y, 
                          dest_x, dest_y,
                          start_orientation,
                          radius, false,
                          r_px, r_py, r_qx, r_qy, 
                          r_angle_start, r_angle_final, r_length);
  
  if (l_possible && r_possible)
    {
      if (l_length < r_length)
        {
          add_radial_segment(l_px, l_py, radius, l_angle_start, l_angle_final, false);
          add_straight_segment(l_qx, l_qy, dest_x, dest_y);
        }
      else
        {
          add_radial_segment(r_px, r_py, radius, r_angle_start, r_angle_final, false);
          add_straight_segment(r_qx, r_qy, dest_x, dest_y); 
        }
    }
  else if (l_possible)
    {
      add_radial_segment(l_px, l_py, radius, l_angle_start, l_angle_final, false);
      add_straight_segment(l_qx, l_qy, dest_x, dest_y);
    }
  else if (r_possible)
    {
      add_radial_segment(r_px, r_py, radius, r_angle_start, r_angle_final, false);
      add_straight_segment(r_qx, r_qy, dest_x, dest_y);
    }
  else
    {
      assert(false);
    }
}

void
LineSegments::draw(View* view)
{
  //std::cout << "-----: " << segments.size()  << std::endl;
  for(Segments::iterator i = segments.begin(); i != segments.end(); ++i)
    {
      switch(i->type)
        {
        case RADIAL:
          //std::cout << "Radial: " << (int)i->radial.x << ", " <<(int)i->radial.y
            //        << " " << (int)i->radial.radius << std::endl;
          view->draw_circle((int)i->radial.x, (int)i->radial.y, (int)i->radial.radius,
                            1.0f, 1.0f, 1.0f, 1.0f);
          break;
        case STRAIGHT:
          view->draw_line((int)i->straight.x1, (int)i->straight.y1,
                          (int)i->straight.x2, (int)i->straight.y2, 
                          1.0f, 1.0f, 1.0f, 1.0f);
          break;
        default:
          std::cout << "Unhandled type: " << i->type << std::endl;
          break;
        }
    }
}

/* EOF */
