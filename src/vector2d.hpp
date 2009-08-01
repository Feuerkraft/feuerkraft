//  $Id: vector2d.hpp,v 1.6 2003/08/20 00:15:10 grumbel Exp $
// 
//  Feuerkraft - A Tank Battle Game
//  Copyright (C) 2002 Ingo Ruhnke <grumbel@gmx.de>
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

#ifndef HEADER_VECTOR2D_HXX
#define HEADER_VECTOR2D_HXX

#include <iosfwd>

/** */
struct IntVector2d
{
  int x;
  int y;
};

class FloatVector2d
{
public:
  float x;
  float y;

  FloatVector2d();
  FloatVector2d(const FloatVector2d& vec) : x(vec.x), y(vec.y) {};
  FloatVector2d(float arg_x, float arg_y);

  /** Create a vector with the given polar coordinates */
  static FloatVector2d make_polar(float length, float orientation);

  /** 
   * Set the orienentation of a vector to \a angle
   * 
   * @param angle in radian
   */
  void set_orientation(float angle);

  /** 
   * Rotate a vector by modifing it
   * 
   * @param angle in radian
   */
  FloatVector2d& rotate(float angle);

  /** @return Length of the vector */
  float get_length() const;

  /** @return abs(x) + abs(y) */
  inline float get_manhatten_length() const;

  /** @return the current orienentation of the vector in radian */
  float get_orientation() const;

  FloatVector2d operator- () const;

  FloatVector2d operator+ (const FloatVector2d& add) const;
  FloatVector2d operator- (const FloatVector2d& sub) const;
  FloatVector2d operator* (       float  mul) const;

  FloatVector2d& operator+= (const FloatVector2d& add);
  FloatVector2d& operator-= (const FloatVector2d& sub);
  FloatVector2d& operator*= (      float   mul);

  friend std::ostream& operator<< (std::ostream& os, const FloatVector2d& v);
};

std::ostream& operator<< (std::ostream& os, const FloatVector2d& v);

#endif

/* EOF */
