// Feuerkraft - A Tank Battle Game
// Copyright (C) 2002 Ingo Ruhnke <grumbel@gmx.de>
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

#include <math.h>
#include <iostream>
#include "vector2d.hpp"

FloatVector2d::FloatVector2d()
  : x(0.0f), y(0.0f)
{
}

FloatVector2d::FloatVector2d(float arg_x, float arg_y)
  : x(arg_x), y(arg_y)
{
}

FloatVector2d
FloatVector2d::make_polar(float length, float orientation)
{
  return FloatVector2d(cos(orientation) * length,
                       sin(orientation) * length);
}

void
FloatVector2d::set_orientation(float angle)
{
  x = sin(angle) * get_length();
  y = cos(angle) * get_length();
}

FloatVector2d&
FloatVector2d::rotate(float angle)
{
  float length = get_length();
  float orientation = get_orientation();

  x = cos(orientation + angle) * length;
  y = sin(orientation + angle) * length;
  return *this;
}

float
FloatVector2d::get_length() const
{
  return sqrt(x*x + y*y);
}

float
FloatVector2d::get_manhatten_length() const
{
  return fabsf(x) + fabsf(y);
}

float
FloatVector2d::get_orientation() const
{
  return atan2(y, x);
}

FloatVector2d
FloatVector2d::operator- () const
{
  return FloatVector2d(-x, -y);
}

FloatVector2d
FloatVector2d::operator+ (const FloatVector2d& add) const
{
  return FloatVector2d(x + add.x,
                       y + add.y);
}

FloatVector2d
FloatVector2d::operator- (const FloatVector2d& sub) const
{
  return FloatVector2d(x - sub.x,
                       y - sub.y);
}

FloatVector2d
FloatVector2d::operator* (float  mul) const
{
  return FloatVector2d(x * mul, y * mul);
}

FloatVector2d&
FloatVector2d::operator+= (const FloatVector2d& add)
{
  x += add.x;
  y += add.y;
  return *this;
}

FloatVector2d&
FloatVector2d::operator-= (const FloatVector2d& sub)
{
  x -= sub.x;
  y -= sub.y;
  return *this;
}

FloatVector2d&
FloatVector2d::operator*= (float   mul)
{
  x *= mul;
  y *= mul;
  return *this;
}

std::ostream& operator<< (std::ostream& os, const FloatVector2d& v)
{
  return os << "(" << v.x << ", " << v.y << ")";
}

/* EOF */
