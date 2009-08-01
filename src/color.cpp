//  $Id: color.cpp,v 1.2 2003/06/03 14:11:22 grumbel Exp $
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

#include "color.hpp"

Color::Color()
{
  red   = 1.0f;
  green = 1.0f;
  blue  = 1.0f;
  alpha = 1.0f;
}

Color::Color(float red_, float green_, float blue_, float alpha_)
{
  red   = red_;
  green = green_;
  blue  = blue_;
  alpha = alpha_;
}

CL_Color
Color::get_cl_color() const
{
  return CL_Color(static_cast<int>(255 * red),
                  static_cast<int>(255 * green),
                  static_cast<int>(255 * blue),
                  static_cast<int>(255 * alpha));
}

/* EOF */
