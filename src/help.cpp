//  $Id: help.cpp,v 1.2 2003/06/06 11:11:19 grumbel Exp $
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

#include <ClanLib/Display/display.h>
#include "fonts.hpp"
#include "help.hpp"

Help::Help()
{
  font = Fonts::font;
}

Help::~Help()
{
}

void
Help::draw(CL_GraphicContext& gc)
{
  int center_x = CL_Display::get_width()/2;
  int center_y = CL_Display::get_height()/2;

  CL_Display::fill_rect(CL_Rect(center_x - 200, center_y - 150,
                                center_x + 200, center_y + 150),
                        CL_Color(100, 100, 0, 230));
  font.set_alignment(origin_top_left);
  font.draw(center_x - 190, center_y - 120, 
            "F1 - show/hide this help screen\n"
            "Esc - leave game\n"
            "j  - enter/leave a vehicle\n"
            "left - turn left\n"
            "right - turn right\n"
            );
}

void
Help::update(float delta)
{
}

/* EOF */
