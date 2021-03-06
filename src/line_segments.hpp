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

#ifndef HEADER_LINE_SEGMENTS_HXX
#define HEADER_LINE_SEGMENTS_HXX

#include "vector2d.hpp"
#include <vector>

class View;

/** */
class LineSegments
{
private:
  enum { STRAIGHT, RADIAL };

  struct StraightSegment {
    float x1, y1; ///< start
    float x2, y2; ///< goal
  };

  struct RadialSegment {
    float x, y;        ///< position of the circle
    float radius;      ///< radius of the circle
    float start_angle; ///< start angle in radians
    float end_angle;   ///< end angle in radians
    bool  turn_right;  ///< true if counterclockwise
  };

  // FIXME: Replace me with OO
  struct Segment {
    int   type;   ///< type of the segment
    float length; ///< length of the segment, calculated from the segment

    union {
      struct RadialSegment   radial;
      struct StraightSegment straight;
    };
  };

  typedef std::vector<Segment> Segments;
  Segments segments;

  float init_x, init_y, init_orientation;

  float calc_length(const Segment&);
  Segments::iterator get_segment(float l);

  /** @return the position on the line segment after having traveled
      \a l 'pixels' on it */
  FloatVector2d get_pos(const Segment&, float l);
  float     get_orientation(const Segment&, float l);

  bool calc_route(float start_x, float start_y,
                  float dest_x, float dest_y,
                  float start_orientation,
                  float radius, bool turn_right,
                  float& px, float& py, float& qx, float& qy,
                  float& angle_start, float& angle_final, float& length);
public:
  LineSegments(float init_x, float init_y, float init_orientation);

  float     get_end_orientation();
  FloatVector2d get_end_pos();

  FloatVector2d get_pos(float l);
  float     get_orientation(float l);

  /** @return length of all segments together */
  float get_length();

  /** Remove all segments */
  void clear();

  /** Set the position of the line segment */
  void set_pos(float init_x, float init_y, float init_orientation);

  void add_straight_segment(float x1, float y1, float x2, float y2);
  void add_radial_segment(float x, float y, float radius,
                          float start_angle, float stop_angle, bool turn_right);

  /** Generate one or more segments to the given controll point */
  void add_controll_point(float x, float y, float turn_radius);

  /** Some code to draw the path for debugging */
  void draw(View& view);
};

#endif

/* EOF */
