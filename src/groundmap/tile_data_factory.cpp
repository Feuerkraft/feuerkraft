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

#include "tile_data.hpp"
#include "sprite_tile_data.hpp"
#include "sprite_tile.hpp"
#include "tile_data_factory.hpp"

TileData*
TileDataFactory::create (SCM desc)
{
  SCM symbol = scm_car (desc);
  SCM data   = scm_cdr (desc);

  if (scm_equal_p (scm_from_utf8_symbol ("spritetile"), symbol))
    {
      return create_SpriteTileData (data);
    }
  else
    {
      std::cout << "TileDataFactory: Unknown tile type: '" << std::flush;
      scm_display (symbol, SCM_UNDEFINED);
      std::cout << "' with data: " << std::flush;
      scm_display (data, SCM_UNDEFINED);
      std::cout << std::endl;
      return 0;
    }
}

SpriteTileData*
TileDataFactory::create_SpriteTileData (SCM desc)
{
  SpriteTileData* sprite_data = new SpriteTileData ();

  //std::cout << "TileDataFactory:create_SpriteTileData:" << std::flush;
  //scm_display (desc, SCM_UNDEFINED);
  //std::cout << std::endl;

  while (!scm_null_p (desc))
    {
      SCM symbol = scm_caar(desc);
      SCM data   = scm_cdar(desc);

      if (scm_equal_p (scm_from_utf8_symbol ("location"), symbol))
	{
	  char* str = scm_to_utf8_string(scm_car(data));
	  sprite_data->sprite_location = str;
#ifndef WIN32	// Freeing this crashed under VisualC++
	  free (str);
#endif
	}
      else
	{
	  std::cout << "TileDataFactory: Unknown sprite tile type: '" << std::flush;
	  scm_display (symbol, SCM_UNDEFINED);
	  std::cout << "' with data: " << std::flush;
	  scm_display (data, SCM_UNDEFINED);
	  std::cout << std::endl;
	  return 0;
	}

      desc = scm_cdr (desc);
    }

  return sprite_data;
}

/* EOF */
