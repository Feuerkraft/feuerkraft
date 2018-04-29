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
#include "tile_map_data.hpp"
#include "multi_ground_map.hpp"
#include "grid_map_data.hpp"
#include "ground_map_data_factory.hpp"
#include "guile.hpp"

GroundMapData*
GroundMapDataFactory::create (SCM desc)
{
  MultiGroundMapData* multigroundmap = new MultiGroundMapData ();

  /*std::cout << "GroundMapFactory: desc: "<< std::flush;
  scm_display (desc, SCM_UNDEFINED);
  scm_newline ();*/

  while (scm_is_true(scm_pair_p (desc)))
    {
      SCM symbol = scm_caar (desc);
      SCM data   = scm_cdar (desc);

      /*
      std::cout << "GroundMapFactory: symbol: "<< std::flush;
      scm_display (symbol, SCM_UNDEFINED);
      scm_newline ();

      std::cout << "GroundMapFactory: data: "<< std::flush;
      scm_display (data, SCM_UNDEFINED);
      scm_newline ();
      */
      if (Guile::equal_p (scm_from_utf8_symbol ("tilemap"), symbol))
	{
	  multigroundmap->add(new TileMapData (data));
	}
      else if (Guile::equal_p (scm_from_utf8_symbol ("gridmap"), symbol))
	{
	  multigroundmap->add(new GridMapData (data));
	}
      else
	{
	  std::cout << "GroundMapFactory: Unknown map type: " << std::flush;
	  scm_display (symbol, SCM_UNDEFINED);
	  scm_newline (SCM_UNDEFINED);
	  //return 0;
	}

      desc = scm_cdr (desc);
    }

  return multigroundmap;
}

/* EOF */
