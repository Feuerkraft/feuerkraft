//  $Id$
// 
//  Pingus - A free Lemmings clone
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

#ifndef HEADER_AXIS_FACTORY_HXX
#define HEADER_AXIS_FACTORY_HXX

#include <guile/gh.h>
#include "input_axis.hpp"

/** */
class AxisFactory
{
public:
  static InputAxis* create(SCM lst);
private:
  static InputAxis* create_joystick_axis(SCM lst);
  static InputAxis* create_button_axis(SCM lst);
};

#endif

/* EOF */
