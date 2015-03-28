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

#include "math.hpp"

namespace Math {


bool quad_collide(const Quad& quad1, const Quad& quad2)
{
  // add bounding box check here

  if (lines_intersect(quad1.a, quad1.b,
                      quad2.a, quad2.b))
    return true;
  else if (lines_intersect(quad1.b, quad1.c,
                           quad2.a, quad2.b))
    return true;
  else if (lines_intersect(quad1.c, quad1.d,
                           quad2.a, quad2.b))
    return true;
  else if (lines_intersect(quad1.d, quad1.a,
                           quad2.a, quad2.b))
    return true;
  // snip
  else if (lines_intersect(quad1.a, quad1.b,
                           quad2.b, quad2.c))
    return true;
  else if (lines_intersect(quad1.b, quad1.c,
                           quad2.b, quad2.c))
    return true;
  else if (lines_intersect(quad1.c, quad1.d,
                           quad2.b, quad2.c))
    return true;
  else if (lines_intersect(quad1.d, quad1.a,
                           quad2.b, quad2.c))
    return true;
  // snip
  else if (lines_intersect(quad1.a, quad1.b,
                           quad2.c, quad2.d))
    return true;
  else if (lines_intersect(quad1.b, quad1.c,
                           quad2.c, quad2.d))
    return true;
  else if (lines_intersect(quad1.c, quad1.d,
                           quad2.c, quad2.d))
    return true;
  else if (lines_intersect(quad1.d, quad1.a,
                           quad2.c, quad2.d))
    return true;
  // snip
  else if (lines_intersect(quad1.a, quad1.b,
                           quad2.d, quad2.a))
    return true;
  else if (lines_intersect(quad1.b, quad1.c,
                           quad2.d, quad2.a))
    return true;
  else if (lines_intersect(quad1.c, quad1.d,
                           quad2.d, quad2.a))
    return true;
  else if (lines_intersect(quad1.d, quad1.a,
                           quad2.d, quad2.a))
    return true;

  else // no lines intersect, but one quad might be completly inside of another quad
    {
      if (point_inside_quad(quad1.a, quad2)
          || point_inside_quad(quad1.b, quad2)
          || point_inside_quad(quad1.c, quad2)
          || point_inside_quad(quad1.d, quad2))
        return true;
      else if (point_inside_quad(quad2.a, quad1)
               || point_inside_quad(quad2.b, quad1)
               || point_inside_quad(quad2.c, quad1)
               || point_inside_quad(quad2.d, quad1))
        return true;
      else
        return false;
    }
}

bool point_inside_quad(const Point& point, const Quad& quad)
{
  Triangle triangle1, triangle2;

  triangle1.a = quad.a;
  triangle1.b = quad.b;
  triangle1.c = quad.c;

  triangle2.a = quad.b;
  triangle2.b = quad.c;
  triangle2.c = quad.d;

  return point_inside_triangle(point, triangle1)
    || point_inside_triangle(point, triangle2);
}

} // namespace Math

/* EOF */
