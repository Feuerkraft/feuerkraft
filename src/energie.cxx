//  $Id: energie.cxx,v 1.7 2003/05/19 19:00:56 grumbel Exp $
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

#include "color.hxx"
#include "view.hxx"
#include "energie.hxx"

Energie::Energie ()
{
  max_energie = 100.0f;
  energie = max_energie;
  last_change = 0;
}

void
Energie::set_max_energie(float arg_max_energie)
{
  max_energie = arg_max_energie;
  energie = max_energie;
}

Energie::Energie (int arg_energie) :
  max_energie (arg_energie),
  energie (arg_energie),
  last_change (0)
{
  
}

void
Energie::draw (View& view, int x_pos, int y_pos)
{
  int time_diff = CL_System::get_time () - last_change ;

  float ratio = energie / max_energie;
  
  if (ratio < 0)
    ratio = 0;

  //  std::cout << "Ratio: " << ratio << std::endl;

  if (time_diff < 1000
      && CL_System::get_time () > 2000)
    {
      // Black border rectangle
      view.draw_fillrect (x_pos - 32, y_pos - 5,
			   x_pos + 32, y_pos + 5,
			   Color(0.0f, 0.0f, 0.0f,
                                 (1000.0f - float(time_diff))/1000.0f * 0.8f));
      
      // Energie bar
      view.draw_fillrect (x_pos - 30, y_pos - 3,
			   int(x_pos - 30 + (ratio * 60)),
			   y_pos + 3,
			   Color(1.0f - energie/float(max_energie),
                                 ratio,
                                 0.0f, 
                                 (1000.0f - float(time_diff)) / 1000.0f * 0.9f));
      //std::cout << "Alpha: " << float(time_diff) / 500.0 << std::endl;
    }
}

/* EOF */
