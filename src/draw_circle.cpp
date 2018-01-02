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

#include <iostream>
#include "draw_circle.hpp"

#ifdef TESTME
int main()
{
  Field<int> field(50, 50);
  srand(time(NULL));
  //draw_circle(field, 20, 20, 12);
  draw_fill_circle(field, 20, 20, 12);
  //draw_fill_circle(field, 30, 30, 6);

  for(int count = 0; count < 40; ++count)
    draw_fill_circle(field, (rand()%29)+10, (rand()%29)+10, rand()%9);

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
#endif

// Local Variables:
// compile-command: "g++-3.2 -DTESTME -Wall -O2 draw_circle.cpp  -o draw_circle -lclanCore"
// End:

/* EOF */
