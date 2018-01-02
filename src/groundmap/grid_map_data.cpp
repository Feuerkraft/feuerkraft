// Feuerkraft - A Tank Battle Game
// Copyright (C) 2000 Ingo Ruhnke <grumbel@gmail.com>
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
#include <ClanLib/Display/Providers/png_provider.h>

#include "../path_manager.hpp"
#include "grid_map.hpp"
#include "grid_map_data.hpp"

GridMapData::GridMapData (SCM desc)
{
  grid_width  = -1;
  grid_height = -1;

  while (!scm_null_p (desc))
    {
      SCM symbol = scm_caar(desc);
      SCM data   = scm_cdar(desc);

      if (scm_equal_p (scm_from_utf8_symbol ("file"), symbol))
        {
          parse_from_file (data);
        }
      else
        {
          std::cout << "GridMapData: Unknown data type: '" << std::flush;
          scm_display (symbol, SCM_UNDEFINED);
          std::cout << "' with data: " << std::flush;
          scm_display (data, SCM_UNDEFINED);
          std::cout << std::endl;
          return;
        }

      desc = scm_cdr (desc);
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
  char* str = scm_to_utf8_string(scm_car (desc));
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
