//  $Id: line_segments.hxx,v 1.1 2003/05/04 09:31:49 grumbel Exp $
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

#ifndef HEADER_LINE_SEGMENTS_HXX
#define HEADER_LINE_SEGMENTS_HXX

#include <ClanLib/Core/Math/cl_vector.h>
#include <vector>
          
/** */
class LineSegments
{
private:
  enum { STRAIGHT, RADIAL };

  struct StraightSegment {
    int type;
    float length;

    float x1, y1; //< start
    float x2, y2; //< goal
  };

  struct RadialSegment {
    int type;
    float length;

    float x, y;
    float radius;
    float start_angle;
    float end_angle;
  };
  
  union Segment {
    int type;
    float length;

    struct RadialSegment   radial;
    struct StraightSegment straight;
  };

  typedef std::vector<Segment> Segments;
  Segments segments;
  
  float calc_length(const Segment&);
  Segments::iterator get_segment(float l);

  /** @return the position on the line segment after having traveled
      \a l 'pixels' on it */
  CL_Vector get_pos(const Segment&, float l);

public:
  LineSegments();

  CL_Vector get_pos(float l);

  /** @return length of all segments together */
  float get_length();

  void add_straight_segment(float x1, float y1, float x2, float y2);
  void add_radial_segment(float x, float y, float radius, float start_angle, float stop_angle);
};

#endif

/* EOF */
