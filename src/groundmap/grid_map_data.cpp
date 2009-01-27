//  $Id: grid_map_data.cpp,v 1.5 2003/10/20 20:58:40 grumbel Exp $
//
//  Feuerkraft - A Tank Battle Game
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

#include <iostream>
#include <ClanLib/Display/Providers/png_provider.h>

#include "../path_manager.hpp"
#include "grid_map.hpp"
#include "grid_map_data.hpp"

GridMapData::GridMapData (SCM desc)
{
  grid_width  = -1;
  grid_height = -1;
  
  while (!gh_null_p (desc))
    {
      SCM symbol = gh_caar(desc);
      SCM data   = gh_cdar(desc);

      if (gh_equal_p (gh_symbol2scm ("file"), symbol))
        {
          parse_from_file (data);
        }
      else
        {
          std::cout << "GridMapData: Unknown data type: '" << std::flush;
          gh_display (symbol);
          std::cout << "' with data: " << std::flush;
          gh_display (data);
          std::cout << std::endl;
          return;
        }

      desc = gh_cdr (desc);
    }
}

GridMapData::~GridMapData ()
{
  // delete provider; FIXME: disabled cause it could lead to throuble with copy c'tor
}

void
GridMapData::parse_from_file (SCM desc)
{
  /* GridMaps will always get a one pixel boarder with the base
     enviroment */
  char* str = gh_scm2newstr(gh_car (desc), 0);
  std::cout << "Loading from: " << str << std::endl;
  std::string filename = str;
#ifndef WIN32
  free (str);
#endif

  provider = CL_PNGProvider (path_manager.complete("missions/" + filename));

  provider.lock ();
  //FIXME:Display2 assert (provider.is_indexed ());

  grid_width  = provider.get_width () + 2;
  grid_height = provider.get_height () + 2;

  grid_data.resize (grid_width * grid_height);
  
  for (int i = 0; i < grid_height * grid_width; ++i)
    grid_data[i] = GT_SAND; // FIXME: should be variable not hardcoded!

  unsigned char* buffer = static_cast<unsigned char*>(provider.get_data ());
  for (int y = 0; y < provider.get_height (); ++y)
    for (int x = 0; x < provider.get_width (); ++x)
      grid_data[(x + 1) + ((y+1) * grid_width)] 
	= static_cast<GroundType>(buffer[x + (provider.get_width () * y)]);

  provider.unlock (); 
}

GroundMap*
GridMapData::create ()
{
  return new GridMap (*this);
}

/* EOF */
