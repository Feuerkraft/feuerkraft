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

#include "../path_manager.hpp"
#include "tile_data_factory.hpp"
#include "tile_map_data.hpp"
#include "tile_map.hpp"
#include "guile.hpp"

TileMapData::TileMapData (SCM desc)
{
  width = -1;
  height = -1;

  while (!scm_is_true(scm_null_p (desc)))
    {
      SCM symbol = scm_caar(desc);
      SCM data   = scm_cdar(desc);

      if (Guile::equal_p (scm_from_utf8_symbol ("width"), symbol))
	{
	  width = scm_to_int(scm_car (data));
	}
      else if (Guile::equal_p (scm_from_utf8_symbol ("height"), symbol))
	{
	  height = scm_to_int(scm_car (data));
	}
      else if (Guile::equal_p (scm_from_utf8_symbol ("tiles"), symbol))
	{
	  parse_tiles (data);
	}
      else if (Guile::equal_p (scm_from_utf8_symbol ("file"), symbol))
	{
	  parse_from_file (data);
	}
      else if (Guile::equal_p (scm_from_utf8_symbol ("map"), symbol))
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

  std::string path = path_manager.complete("missions/" + filename);
  SDL_Surface* surface = IMG_Load(path.c_str());
  if (!surface)
    {
      std::cerr << "TileMapData: failed to load " << path
                << ": " << IMG_GetError() << std::endl;
      return;
    }
  SDL_Surface* converted = SDL_ConvertSurfaceFormat(surface, SDL_PIXELFORMAT_INDEX8, 0);
  if (!converted)
    converted = SDL_ConvertSurfaceFormat(surface, SDL_PIXELFORMAT_RGBA32, 0);
  SDL_FreeSurface(surface);
  if (!converted)
    return;

  width  = converted->w;
  height = converted->h;
  tilemap_data.resize (width * height);

  SDL_LockSurface(converted);
  unsigned char* buffer = static_cast<unsigned char*>(converted->pixels);
  int bpp = converted->format->BytesPerPixel;
  int pitch = converted->pitch;
  for (int y = 0; y < height; ++y)
    for (int x = 0; x < width; ++x)
      tilemap_data[x + y * width] = buffer[y * pitch + x * bpp];
  SDL_UnlockSurface(converted);
  SDL_FreeSurface(converted);
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
  while (!scm_is_true(scm_null_p (desc)))
    {
      if (i < static_cast<int>(tilemap_data.size()))
	{
	  tilemap_data[i] = scm_to_int (scm_car (desc));
	  ++i;
	}
      else
	{
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
  while (!scm_is_true(scm_null_p (desc)))
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
