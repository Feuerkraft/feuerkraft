//  $Id: line_segments.cxx,v 1.3 2003/05/04 15:45:34 grumbel Exp $
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
    case RADIAL:
      return 100.0f;
      break;

    case STRAIGHT:
      {
        float xlen = segment.data.straight.x2 - segment.data.straight.x1;
        float ylen = segment.data.straight.y2 - segment.data.straight.y1;
        return sqrt(xlen*xlen + ylen*ylen);
      }
      break;

    default:
      assert(false);
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
  
  Segments::iterator seg = segments.begin();
  while(seg != segments.end())
    {
      len += seg->length;
      if (len > l)
        break;
      ++seg;
    }

  if (seg == segments.end())
    {
      std::cout << "trying to access bejoint last segment: " << l << " " << get_length() << std::endl;
      return get_end_pos();
    }
  else
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
      return atan2(segment.data.straight.y2 - segment.data.straight.y1,
                   segment.data.straight.x2 - segment.data.straight.x1);
      break;

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
      return CL_Vector(segment.data.straight.x2,
                       segment.data.straight.y2);
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
    case RADIAL:
      {
        const float& start_angle = segment.data.radial.start_angle;
        const float& end_angle   = segment.data.radial.end_angle;
        const float& radius      = segment.data.radial.radius;
        
        float angle;
        if (segment.data.radial.turn_right)
          angle = Math::normalize_angle(start_angle - end_angle);
        else
          angle = Math::normalize_angle(end_angle - start_angle);

        float relative = len / (segment.data.radial.radius * angle);
        angle = angle * relative;
        
        return CL_Vector(segment.data.radial.x + cos(angle+start_angle)*radius,
                         segment.data.radial.y + sin(angle+start_angle)*radius);
      }
      break;
    case STRAIGHT:
      {
        // relative position on the segment
        float rel_pos = len/calc_length(segment);
        float xlen    = segment.data.straight.x2 - segment.data.straight.x1;
        float ylen    = segment.data.straight.y2 - segment.data.straight.y1;

        return CL_Vector(segment.data.straight.x1 + (xlen * rel_pos),
                         segment.data.straight.y1 + (ylen * rel_pos));
      }
      break;
    }
  return CL_Vector();
}

void
LineSegments::add_straight_segment(float x1, float y1, float x2, float y2)
{
  Segment segment;

  segment.data.straight.x1 = x1;
  segment.data.straight.y1 = y1;
  segment.data.straight.x2 = x2;
  segment.data.straight.y2 = y2;

  segment.type   = STRAIGHT;
  segment.length = calc_length(segment);
  
  std::cout << "Line length: " << segment.length << std::endl;

  segments.push_back(segment);
}

void
LineSegments::add_radial_segment(float x, float y, float radius, 
                                 float start_angle, float stop_angle, bool turn_right)
{
  Segment segment;

  segment.data.radial.x = x;
  segment.data.radial.y = y;
  segment.data.radial.radius = radius;
  segment.data.radial.start_angle = start_angle;
  segment.data.radial.end_angle   = stop_angle;
  segment.data.radial.turn_right  = turn_right;

  segment.type   = RADIAL;
  segment.length = calc_length(segment);

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

  angle_final = Math::normalize_angle(turn_right ? phi + theta : phi - theta);
  qx = px + radius * cos(angle_final);
  qy = py + radius * sin(angle_final);
  
  angle_start = Math::normalize_angle(angle_to_p + Math::pi);

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
          add_radial_segment(r_px, r_py, radius, r_angle_start, r_angle_final, true);
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
      add_radial_segment(r_px, r_py, radius, r_angle_start, r_angle_final, true);
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
          view->draw_circle((int)i->data.radial.x, (int)i->data.radial.y, (int)i->data.radial.radius,
                            1.0f, 1.0f, 1.0f, .3f);

          {
            int x = int(i->data.radial.x + i->data.radial.radius * cos(i->data.radial.start_angle));
            int y = int(i->data.radial.y + i->data.radial.radius * sin(i->data.radial.start_angle));
            view->draw_fillrect(x-5, y-5,
                                x+5, y+5,
                                0.0, 0.0f, 1.0f);
          }

          {
            int x = int(i->data.radial.x + i->data.radial.radius * cos(i->data.radial.end_angle));
            int y = int(i->data.radial.y + i->data.radial.radius * sin(i->data.radial.end_angle));
            view->draw_fillrect(x-5, y-5,
                                x+5, y+5,
                                1.0, 0.0f, 1.0f);
          }


          if (i->data.radial.turn_right)
            {
              view->draw_arc((int)i->data.radial.x, (int)i->data.radial.y, (int)i->data.radial.radius,
                             i->data.radial.start_angle, i->data.radial.end_angle, 
                             1.0f, 1.0f, 1.0f);
              view->draw_fillrect((int)i->data.radial.x-5, (int)i->data.radial.y-5,
                                  (int)i->data.radial.x+5, (int)i->data.radial.y+5,
                                  0.0f, 0.0f, 1.0f); //blue
            }
          else
            {
              view->draw_arc((int)i->data.radial.x, (int)i->data.radial.y, (int)i->data.radial.radius,
                             i->data.radial.end_angle, i->data.radial.start_angle, 
                             1.0f, 1.0f, 1.0f);
              view->draw_fillrect((int)i->data.radial.x-5, (int)i->data.radial.y-5,
                                  (int)i->data.radial.x+5, (int)i->data.radial.y+5,
                                  1.0f, 0.0f, 0.0f); // red
            }
          break;

        case STRAIGHT:
          view->draw_line((int)i->data.straight.x1, (int)i->data.straight.y1,
                          (int)i->data.straight.x2, (int)i->data.straight.y2, 
                          1.0f, 1.0f, 1.0f, 1.0f);
          break;
        default:
          std::cout << "Unhandled type: " << i->type << std::endl;
          break;
        }
    }

  for(float i = 0; i < get_length(); i += 15)
    {
      CL_Vector pos = get_pos(i);
      //std::cout << "Pos: " << pos << std::endl;
      view->draw_fillrect(int(pos.x-5), int(pos.y-5),
                          int(pos.x+5), int(pos.y+5),
                          1.0f, 0.0f, 0.0f, .5f); // red      
    }
}

/* EOF */
