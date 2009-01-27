//  $Id: line_segments.cxx,v 1.14 2003/06/18 14:38:28 grumbel Exp $
//
//  Feuerkraft - A Tank Battle Game
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
#include "color.hxx"
#include "view.hxx"
#include "line_segments.hxx"

LineSegments::LineSegments(float arg_init_x, float arg_init_y, float arg_init_orientation)
  : init_x(arg_init_x),
    init_y(arg_init_y),
    init_orientation(arg_init_orientation)
{
}

float
LineSegments::get_orientation(const Segment& segment, float len)
{
  switch(segment.type)
    {
    case RADIAL:
      {
        const float& start_angle = segment.radial.start_angle;
        const float& end_angle   = segment.radial.end_angle;
        //const float& radius      = segment.radial.radius;
        
        float angle;

        if (segment.radial.turn_right)
          angle = Math::normalize_angle(end_angle - start_angle);
        else
          angle = Math::normalize_angle(start_angle - end_angle);

        float relative = len / (segment.radial.radius * angle);

        angle = angle * relative;

        if (segment.radial.turn_right)
          return start_angle + angle + Math::pi_2;
        else
          return start_angle - angle - Math::pi_2;
      }
      break;

    case STRAIGHT:
      {
        return atan2(segment.straight.y2 - segment.straight.y1,
                     segment.straight.x2 - segment.straight.x1);
      }
      break;

    default:
      assert(false);
    }
  return 0;  
}

float
LineSegments::calc_length(const Segment& segment)
{
  switch(segment.type)
    {
    case RADIAL:
      {
        if (segment.radial.turn_right)
          {
            float angle = Math::normalize_angle(segment.radial.end_angle - segment.radial.start_angle);
            return angle * segment.radial.radius;
          }
        else
          {
            float angle = Math::normalize_angle(segment.radial.start_angle - segment.radial.end_angle);
            return angle * segment.radial.radius;
          }
      }
      break;

    case STRAIGHT:
      {
        float xlen = segment.straight.x2 - segment.straight.x1;
        float ylen = segment.straight.y2 - segment.straight.y1;
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

float
LineSegments::get_orientation(float l)
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
      return get_end_orientation();
    }
  else
    return get_orientation(*seg, seg->length - (len - l));
}

FloatVector2d
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
  if (segments.size() > 0)
    {
      Segment& segment = segments.back();
  
      switch (segment.type)
        {
        case STRAIGHT:
          return atan2(segment.straight.y2 - segment.straight.y1,
                       segment.straight.x2 - segment.straight.x1);
          break;

        case RADIAL:
      
          break;
        }
      return 0;
    }
  else
    {
      return init_orientation;
    }
}

FloatVector2d
LineSegments::get_end_pos()
{
  if (segments.size() > 0)
    {
      Segment& segment = segments.back();
      switch (segment.type)
        {
        case STRAIGHT:
          return FloatVector2d(segment.straight.x2,
                           segment.straight.y2);
        case RADIAL:
          return FloatVector2d(segment.radial.x + segment.radial.radius * cos(segment.radial.end_angle),
                           segment.radial.y + segment.radial.radius * sin(segment.radial.end_angle));
          break;
        }
      return FloatVector2d();
    }
  else
    {
      return FloatVector2d(init_x, init_y);
    }
}

float
LineSegments::get_length()
{
  float len = 0.0f;

  for(Segments::iterator i = segments.begin(); i != segments.end(); ++i)
    len += i->length;
  
  return len;
}

FloatVector2d
LineSegments::get_pos(const Segment& segment, float len)
{
  switch(segment.type)
    {
    case RADIAL:
      {
        const float& start_angle = segment.radial.start_angle;
        const float& end_angle   = segment.radial.end_angle;
        const float& radius      = segment.radial.radius;
        
        float angle;

        if (segment.radial.turn_right)
          angle = Math::normalize_angle(end_angle - start_angle);
        else
          angle = Math::normalize_angle(start_angle - end_angle);

        float relative = len / (segment.radial.radius * angle);

        angle = angle * relative;

        if (segment.radial.turn_right)
          return FloatVector2d(segment.radial.x + cos(start_angle + angle)*radius,
                           segment.radial.y + sin(start_angle + angle)*radius);
        else
          return FloatVector2d(segment.radial.x + cos(start_angle - angle)*radius,
                           segment.radial.y + sin(start_angle - angle)*radius);
      }
      break;
    case STRAIGHT:
      {
        // relative position on the segment
        float rel_pos = len/calc_length(segment);
        float xlen    = segment.straight.x2 - segment.straight.x1;
        float ylen    = segment.straight.y2 - segment.straight.y1;

        return FloatVector2d(segment.straight.x1 + (xlen * rel_pos),
                         segment.straight.y1 + (ylen * rel_pos));
      }
      break;
    }
  return FloatVector2d();
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
  
  //std::cout << "Line length: " << segment.length << std::endl;

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
      //std::cout << "Couldn't generate line segment" << std::endl;
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
      std::cout << "LineSegment: Already at the requested controll point, doing nothing" << std::endl;
    }
}

void
LineSegments::clear()
{
  segments.clear();  
}

void
LineSegments::draw(View& view)
{
#if 0
  for(float i = 0; i < get_length(); i += 15)
    {
      FloatVector2d pos = get_pos(i);
      //std::cout << "Pos: " << pos << std::endl;
      view->draw_fillrect(int(pos.x-5), int(pos.y-5),
                          int(pos.x+5), int(pos.y+5),
                          1.0f, 0.0f, 0.0f, .5f); // red      
    }
#endif

  //std::cout << "-----: " << segments.size()  << std::endl;
  for(Segments::iterator i = segments.begin(); i != segments.end(); ++i)
    {
      switch(i->type)
        {
        case RADIAL:
          //std::cout << "Radial: " << (int)i->radial.x << ", " <<(int)i->radial.y
          //        << " " << (int)i->radial.radius << std::endl;
          /*
          view->draw_circle((int)i->radial.x, (int)i->radial.y, (int)i->radial.radius,
          Color(1.0f, 1.0f, 1.0f, .3f));*/


          if (i->radial.turn_right)
            {
              view.get_sc().color().draw_arc(i->radial.x, i->radial.y, i->radial.radius,
                                     i->radial.start_angle, i->radial.end_angle, 
                                     CL_Color(255, 255, 255));
              /*
              view.draw_fillrect((int)i->radial.x-5, (int)i->radial.y-5,
                                  (int)i->radial.x+5, (int)i->radial.y+5,
                                  Color(0.0f, 0.0f, 1.0f)); //blue
              */
            }
          else
            {
              view.get_sc().color().draw_arc(i->radial.x, i->radial.y, i->radial.radius,
                                     i->radial.end_angle, i->radial.start_angle, 
                                     CL_Color(255, 255, 255));
              /*
              view.draw_fillrect(i->radial.x-5, i->radial.y-5,
                                  i->radial.x+5, i->radial.y+5,
                                  Color(1.0f, 0.0f, 0.0f)); // red
              */
            }
          /*
          {
            int x = int(i->radial.x + i->radial.radius * cos(i->radial.start_angle));
            int y = int(i->radial.y + i->radial.radius * sin(i->radial.start_angle));
            view.draw_fillrect(x-5, y-5,
                                x+5, y+5,
                                Color(0.0, 0.0f, 1.0f));
          }

          {
            int x = int(i->radial.x + i->radial.radius * cos(i->radial.end_angle));
            int y = int(i->radial.y + i->radial.radius * sin(i->radial.end_angle));
            view.draw_fillrect(x-5, y-5,
                                x+5, y+5,
                                Color(1.0, 0.0f, 1.0f));
          }*/
          break;

        case STRAIGHT:
          view.get_sc().color().draw_line(i->straight.x1, i->straight.y1,
                                  i->straight.x2, i->straight.y2, 
                                  CL_Color(255, 255, 255, 255));
          break;
        default:
          std::cout << "Unhandled type: " << i->type << std::endl;
          break;
        }
    }
}

void
LineSegments::set_pos(float arg_init_x, float arg_init_y, float arg_init_orientation)
{
  init_x = arg_init_x;
  init_y = arg_init_y;
  init_orientation = arg_init_orientation;
}

/* EOF */
