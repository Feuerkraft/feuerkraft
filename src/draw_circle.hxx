//  $Id: draw_circle.hxx,v 1.2 2003/05/01 20:56:39 grumbel Exp $
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

#ifndef HEADER_DRAW_CIRCLE_HXX
#define HEADER_DRAW_CIRCLE_HXX

#include <stdlib.h>
#include "math.hxx"
#include "field.hxx"

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
// compile-command: "g++-3.2 -DTESTME -Wall -O2 draw_circle.cxx  -o draw_circle -lclanCore"
// End:

/* EOF */
