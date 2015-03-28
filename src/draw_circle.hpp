//  $Id: draw_circle.hpp,v 1.3 2003/06/03 14:11:22 grumbel Exp $
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

#ifndef HEADER_DRAW_CIRCLE_HXX
#define HEADER_DRAW_CIRCLE_HXX

#include <stdlib.h>
#include "math.hpp"
#include "field.hpp"

// FIXME: no clipping
void draw_fill_circle(Field<int>& field, int center_x, int center_y, int radius)
{
  int xchange = 1 - 2*radius;
  int ychange = 1;
  int x = radius;
  int y = 0;
  int radius_error = 0;
  int pos[radius + 1];

  while (x >= y)
    {
      pos[y] = x;
      pos[x] = y;

      ++y;
      radius_error += ychange;
      ychange += 2;
      if (2*radius_error + xchange > 0)
        {
          --x;
          radius_error += xchange;
          xchange += 2;
        }
    }

  if (center_x > 0 && center_x < field.get_width())
    for(int y = -pos[0]; y <= pos[0]; ++y)
      ++field(center_x, center_y + y);

  for(int x = 1; x <= radius; ++x)
    for(int y = -pos[x]; y <= pos[x]; ++y)
      {
        ++field(center_x + x, center_y + y);
        ++field(center_x - x, center_y + y);
      }
}

/** */
void draw_circle(Field<int>& field, int center_x, int center_y, int radius)
{
  int xchange = 1 - 2*radius;
  int ychange = 1;
  int x = radius;
  int y = 0;
  int radius_error = 0;

  while (x >= y)
    {
      field(center_x + x, center_y + y) = 8;
      field(center_x - x, center_y + y) = 8;
      field(center_x + x, center_y - y) = 8;
      field(center_x - x, center_y - y) = 8;

      field(center_x + y, center_y + x) = 8;
      field(center_x - y, center_y + x) = 8;
      field(center_x + y, center_y - x) = 8;
      field(center_x - y, center_y - x) = 8;

      ++y;
      radius_error += ychange;
      ychange += 2;
      if (2*radius_error + xchange > 0)
        {
          --x;
          radius_error += xchange;
          xchange += 2;
        }
    }
}

#endif

// Local Variables:
// compile-command: "g++-3.2 -DTESTME -Wall -O2 draw_circle.cpp  -o draw_circle -lclanCore"
// End:

/* EOF */
