//  $Id: vector2d.hxx,v 1.1 2003/05/18 11:39:00 grumbel Exp $
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

  FloatVector2d(float arg_x, float arg_y);

  /** 
   * Set the orienentation of a vector to \a angle
   * 
   * @param angle in radian
   */
  void set_orientation(float angle);

  /** 
   * Rotate a vector
   * 
   * @param angle in radian
   */
  void rotate(float angle);

  /** @return Length of the vector */
  float get_length() const;

  /** @return abs(x) + abs(y) */
  float get_manhatten_length() const;

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
