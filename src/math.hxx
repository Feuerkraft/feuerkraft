//  $Id: math.hxx,v 1.5 2003/06/03 14:11:22 grumbel Exp $
// 
//  Feuerkraft - A Tank Battle Game
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

#ifndef HEADER_PINGUS_MATH_HXX
#define HEADER_PINGUS_MATH_HXX

#include <stdlib.h>

/** A collection of small math helper functions, some of them might be
    equal in functionality to standard STL functions, but provided
    here for portability and broken STL implementations 
    
    @brief A collection of mathematical helper functions */
namespace Math {

const double pi   = 3.14159265358979323846;	/* pi */
const double pi_2 = 1.57079632679489661923;	/* pi/2 */

const double east  = 0;
const double north = pi_2;
const double west  = pi;
const double south = 3.0*pi_2;

inline double deg2rad(double deg) 
{
  return deg / 180.0 * pi;
}

inline double rad2deg(double rad) 
{
  return rad / pi * 180;
}

template<class T> 
T min (const T& a, const T& b) 
{
  if (a < b)
    return a;
  else
    return b;
}

template<class T> 
T max (const T& a, const T& b) 
{
  if (a > b)
    return a;
  else
    return b;
}

template<class T> 
T mid (const T& a, const T& b, const T& c) 
{
  return max((a), min((b), (c)));
}

inline
double frand()
{
  return double(rand()) / (RAND_MAX+1.0);
}

inline
bool rand_bool()
{
  return rand()%2 == 0;
}

inline 
float normalize_angle(float angle)
{
  if (angle < 0)
    return normalize_angle(angle + 2*pi);
  else if (angle > 2*pi)
    return normalize_angle(angle - 2*pi);
  else 
    return angle;
}

struct Point {
  float x, y;
};

struct Triangle {
  Point a;
  Point b;
  Point c;
};

struct Quad {
  Point a;
  Point b;
  Point c;
  Point d;
};

inline
bool lines_intersect(float x1, float y1, float x2, float y2,
                     float x3, float y3, float x4, float y4)
{
  float b_x = x2 - x1;
  float b_y = y2 - y1;

  float d_x = x4 - x3;
  float d_y = y4 - x3;

  // The lines are parallel
  if ((b_y*d_x - b_x*d_y) == 0.0)
    return false;
  
  float lambda = ((y3*d_x - x3*d_y) + (x1*d_y - y1*d_x)) / (b_y*d_x - b_x*d_y);
  float mu;

  if (d_x != 0.0)
    mu = (x1 + (lambda * b_x) - x3) / d_x;
  else
    mu = (y1 + (lambda * b_y) - y3) / d_y;
  
  return (lambda >= 0 && lambda <= 1.0
          && mu >= 0 && mu <= 1.0);
}

inline
bool lines_intersect(const Point& a1, const Point& a2,
                     const Point& b1, const Point& b2)
{
  return lines_intersect(a1.x, a1.y, a2.x, a2.y,
                         b1.x, b1.y, b2.x, b2.y);
}

bool point_inside_triangle(float px, float py,
                           float x1, float y1, float x2, float y2, float x3, float y3);

inline
bool point_inside_triangle(const Point p, const Triangle& triangle)
{
  return point_inside_triangle(p.x, p.y,
                               triangle.a.x, triangle.a.y,
                               triangle.b.x, triangle.b.y,
                               triangle.c.x, triangle.c.y);
}

inline
bool point_inside_triangle(float px, float py,
                           float x1, float y1, float x2, float y2, float x3, float y3)
{
  float b0 =  (x2 - x1) * (y3 - y1) - (x3 - x1) * (y2 - y1);
  float b1 = ((x2 - px) * (y3 - py) - (x3 - px) * (y2 - py)) / b0;
  float b2 = ((x3 - px) * (y1 - py) - (x1 - px) * (y3 - py)) / b0;
  float b3 = ((x1 - px) * (y2 - py) - (x2 - px) * (y1 - py)) / b0;
  
  if(b1 > 0 && b2 > 0 && b3 > 0) // strictly inside
    {
      return true;
    }
  else if((b1>=0 && b2>=0 && b3>=0) && (b1+b2+b3) >= 0) // on edge.
    {
      return true;
    }
  else
    {
      return false;
    }
}

bool point_inside_quad(const Point& p, const Quad& q);
bool quad_collide(const Quad& a, const Quad& b);
bool triangle_collide(const Triangle& a, const Triangle& b);

} // namespace Math

#endif

/* EOF */
