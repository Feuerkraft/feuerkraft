//  $Id: math.hxx,v 1.2 2003/05/04 12:12:54 grumbel Exp $
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

} // namespace Math

#endif

/* EOF */
