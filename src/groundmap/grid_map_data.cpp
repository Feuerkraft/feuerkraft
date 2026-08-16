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
#include <SDL.h>
#include <SDL_image.h>

#include "../path_manager.hpp"
#include "grid_map.hpp"
#include "grid_map_data.hpp"
#include "guile.hpp"

GridMapData::GridMapData (SCM desc)
{
  grid_width  = -1;
  grid_height = -1;

  while (!scm_is_true(scm_null_p (desc)))
    {
      SCM symbol = scm_caar(desc);
      SCM data   = scm_cdar(desc);

      if (Guile::equal_p (scm_from_utf8_symbol ("file"), symbol))
        {
          parse_from_file (data);
        }
      else
        {
          std::cout << "GridMapData: Unknown data type: '" << std::flush;
          scm_display (symbol, scm_current_output_port());
          std::cout << "' with data: " << std::flush;
          scm_display (data, scm_current_output_port());
          std::cout << std::endl;
          return;
        }

      desc = scm_cdr (desc);
    }
}

GridMapData::~GridMapData ()
{
}

void
GridMapData::parse_from_file (SCM desc)
{
  /* GridMaps will always get a one pixel border with the base
     environment */
  char* str = scm_to_utf8_string(scm_car (desc));
  std::cout << "Loading from: " << str << std::endl;
  std::string filename = str;
  free (str);

  std::string path = path_manager.complete("missions/" + filename);
  SDL_Surface* surface = IMG_Load(path.c_str());
  if (!surface)
    {
      std::cerr << "GridMapData: failed to load " << path
                << ": " << IMG_GetError() << std::endl;
      return;
    }

  // Convert to indexed/palette or at least a known 8-bit layout if possible
  SDL_Surface* converted = SDL_ConvertSurfaceFormat(surface, SDL_PIXELFORMAT_INDEX8, 0);
  if (!converted)
    {
      // Fall back to reading first byte of each pixel from RGBA
      converted = SDL_ConvertSurfaceFormat(surface, SDL_PIXELFORMAT_RGBA32, 0);
    }
  SDL_FreeSurface(surface);

  if (!converted)
    {
      std::cerr << "GridMapData: convert failed: " << SDL_GetError() << std::endl;
      return;
    }

  grid_width  = converted->w + 2;
  grid_height = converted->h + 2;

  grid_data.resize (grid_width * grid_height);

  for (int i = 0; i < grid_height * grid_width; ++i)
    grid_data[i] = GT_SAND;

  SDL_LockSurface(converted);
  unsigned char* buffer = static_cast<unsigned char*>(converted->pixels);
  int bpp = converted->format->BytesPerPixel;
  int pitch = converted->pitch;

  for (int y = 0; y < converted->h; ++y)
    for (int x = 0; x < converted->w; ++x)
      {
        unsigned char value = buffer[y * pitch + x * bpp];
        grid_data[(x + 1) + ((y + 1) * grid_width)]
          = static_cast<GroundType>(value);
      }
  SDL_UnlockSurface(converted);
  SDL_FreeSurface(converted);
}

GroundMap*
GridMapData::create ()
{
  return new GridMap (*this);
}

/* EOF */
