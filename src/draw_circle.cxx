//  $Id: draw_circle.cxx,v 1.1 2003/04/30 21:27:21 grumbel Exp $
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

#include <iostream>
#include "draw_circle.hxx"

int main()
{
  Field<int> field(40, 40);

  draw_circle(field, 20, 20, 10);
  draw_fill_circle(field, 20, 20, 10);
  //draw_fill_circle(field, 20, 20, 0);
  //draw_fill_circle(field, 20, 20, 2);

  for(int y = 0; y < field.get_height(); ++y)
    {
      for(int x = 0; x < field.get_width(); ++x)
        {
          if (field(x,y) == 0)
            std::cout << " .";
          else 
            std::cout << " " << field(x,y);
        }
      std::cout << std::endl;
    }
}

// Local Variables:
// compile-command: "g++-3.2 -DTESTME -Wall -O2 draw_circle.cxx  -o draw_circle -lclanCore"
// End:

/* EOF */
