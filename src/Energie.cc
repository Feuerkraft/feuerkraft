//  $Id: Energie.cc,v 1.5 2001/03/16 20:36:06 grumbel Exp $
//
//  Pingus - A free Lemmings clone
//  Copyright (C) 2000 Ingo Ruhnke <grumbel@gmx.de>
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

#include <ClanLib/core.h>
#include <ClanLib/display.h>
#include "View.hh"
#include "Energie.hh"

Energie::Energie (int arg_energie) :
  max_energie (arg_energie),
  energie (arg_energie),
  last_change (0)
{
  
}

void
Energie::draw (View* view, int x_pos, int y_pos)
{
  int time_diff = CL_System::get_time () - last_change ;

  if (time_diff < 1000
      && CL_System::get_time () > 2000)
    {
      CL_Display::fill_rect (x_pos - 32, y_pos - 5,
			     x_pos + 32, y_pos + 5,
			     0.0, 0.0, 0.0, (1000.0 - float(time_diff))/1000.0 * 0.8);
      CL_Display::fill_rect (x_pos - 30, y_pos - 3,
			     x_pos - 30 + (energie * 60 / max_energie), y_pos + 3,
			     1.0 - energie/float(max_energie),
			     energie/float(max_energie),
			     0.0, 
			     (1000.0 - float(time_diff)) / 1000.0 * 0.9);
      //std::cout << "Alpha: " << float(time_diff) / 500.0 << std::endl;
    }
}

/* EOF */
