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
#include "tile_data_factory.hpp"
#include "tile_map_data.hpp"
#include "tile_map.hpp"

TileMapData::TileMapData (SCM desc)
{
  width = -1;
  height = -1;

  while (!scm_null_p (desc))
    {
      SCM symbol = scm_caar(desc);
      SCM data   = scm_cdar(desc);

      if (scm_equal_p (scm_from_utf8_symbol ("width"), symbol))
	{
	  width = scm_to_int(scm_car (data));
	}
      else if (scm_equal_p (scm_from_utf8_symbol ("height"), symbol))
	{
	  height = scm_to_int(scm_car (data));
	}
      else if (scm_equal_p (scm_from_utf8_symbol ("tiles"), symbol))
	{
	  parse_tiles (data);
	}
      else if (scm_equal_p (scm_from_utf8_symbol ("file"), symbol))
	{
	  parse_from_file (data);
	}
      else if (scm_equal_p (scm_from_utf8_symbol ("map"), symbol))
	{
	  parse_map (data);
	}
      else
	{
	  std::cout << "TileMapData: Unknown data type: '" << std::flush;
	  scm_display (symbol, SCM_UNDEFINED);
	  std::cout << "' with data: " << std::flush;
	  scm_display (data, SCM_UNDEFINED);
	  std::cout << std::endl;
	  return;
	}

      desc = scm_cdr (desc);
    }
}

TileMapData::~TileMapData ()
{
}

void
TileMapData::parse_from_file (SCM desc)
{
  char* str = scm_to_utf8_string(scm_car(desc));
  std::cout << "Loading from: " << str << std::endl;
  std::string filename = str;
  free (str);

  CL_PNGProvider provider(path_manager.complete("missions/" + filename));

  provider.lock ();
  //FIXME:Display2 assert (provider.is_indexed ());

  width  = provider.get_width ();
  height = provider.get_height ();

  tilemap_data.resize (width * height);

  unsigned char* buffer = static_cast<unsigned char*>(provider.get_data ());
  for (int i = 0; i < width * height; ++i)
    tilemap_data[i] = buffer[i];

  provider.unlock ();
}

void
TileMapData::parse_map (SCM desc)
{
  assert (width != -1);
  assert (height != -1);
  tilemap_data.resize (width * height);

  // Init the map to '0'
  for (std::vector<int>::iterator it = tilemap_data.begin ();
       it != tilemap_data.end (); ++it)
    *it = 0;

  /*std::cout << "Tilemap MapData: " << std::flush;
  scm_display (desc, SCM_UNDEFINED);
  scm_newline ();*/

  int i = 0;
  bool to_large = false;
  while (!scm_null_p (desc))
    {
      if (i < static_cast<int>(tilemap_data.size()))
	{
	  tilemap_data[i] = scm_to_int (scm_car (desc));
	  ++i;
	}
      else
	{
	  to_large = true;
	  ++i;
	}

      desc = scm_cdr(desc);
    }

  std::cout << "TileMapData: map to large: " << width * height
	    << " < " << i << std::endl;
}

void
TileMapData::parse_tiles (SCM desc)
{
  //std::cout << "TileMapData::parse_tiles: " tiles_ << std::endl;
  while (!scm_null_p (desc))
    {
      tiles_data.push_back (TileDataFactory::create (scm_car(desc)));
      desc = scm_cdr (desc);
    }
}

GroundMap*
TileMapData::create ()
{
  return new TileMap (*this);
}

/* EOF */
