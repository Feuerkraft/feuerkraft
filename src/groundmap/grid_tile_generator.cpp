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
#include "../command_line_arguments.hpp"
#include "grid_tile.hpp"
#include "grid_tile_generator.hpp"
#include "guile.hpp"

GridTileGenerator::GridTileGenerator (std::string filename)
  : emptytile (new GridTile ("feuerkraft/emptytile"))
{
  SCM fdes = scm_open_file(scm_from_utf8_string(filename.c_str()),
                           scm_from_utf8_string("r"));
  SCM lst  = scm_read (fdes);

  lst = scm_cdr(lst); // Skip the 'tiles' mark

  while (scm_is_true(scm_pair_p(lst)))
    {
      parse_line (scm_car (lst));
      lst = scm_cdr(lst);
    }

  scm_close (fdes);
}

GridTileGenerator::~GridTileGenerator ()
{
  delete emptytile;
}

void
GridTileGenerator::parse_line (SCM desc)
{
  SCM data = scm_car (desc);
  SCM lst  = scm_cdr (desc);

  GridTileData gdata = scm2GridTileData (data);

  TileTable::iterator i;
  for (i = tiles.begin (); i != tiles.end (); ++i)
    if (i->first == gdata)
      break;

  if (i != tiles.end ())
    {
      std::cout << "GridTileGenerator: collision in file: " << gdata << std::endl;
    }
  else
    {
      tiles.push_back (TileTableEntry(gdata, scm2GridTileVector (lst)));
    }
}

GridTileData
GridTileGenerator::scm2GridTileData (SCM desc)
{
  GridTileData data;
  // FIXME: No error checking here
  data.ul = symbol2GroundType(scm_car (desc));
  data.ur = symbol2GroundType(scm_cadr (desc));
  data.br = symbol2GroundType(scm_caddr (desc));
  data.bl = symbol2GroundType(scm_car(scm_cdddr (desc)));

  return data;
}

GroundType
GridTileGenerator::symbol2GroundType (SCM symbol)
{
  if (Guile::equal_p (scm_from_utf8_symbol ("s"), symbol))
    {
      return GT_SAND;
    }
  else if (Guile::equal_p (scm_from_utf8_symbol ("f"), symbol))
    {
      return GT_FLATWATER;
    }
  else if (Guile::equal_p (scm_from_utf8_symbol ("d"), symbol))
    {
      return GT_DEEPWATER;
    }
  else if (Guile::equal_p (scm_from_utf8_symbol ("g"), symbol))
    {
      return GT_GRASS;
    }
  else if (Guile::equal_p (scm_from_utf8_symbol ("m"), symbol))
    {
      return GT_MUD;
    }
  else if (Guile::equal_p (scm_from_utf8_symbol ("a"), symbol))
    {
      return GT_ASPHALT;
    }
  else if (Guile::equal_p (scm_from_utf8_symbol ("w"), symbol))
    {
      return GT_WETSAND;
    }
  else
    {
      return GT_EMPTY;
    }
}

std::vector<GridTile*>
GridTileGenerator::scm2GridTileVector (SCM desc)
{
  std::vector<GridTile*> vec;

  while (scm_is_true(scm_pair_p(desc)))
    {
      char* str = scm_to_utf8_string(scm_car(desc));
      vec.push_back (new GridTile (str));

#ifndef WIN32
      free (str);
#endif

      desc = scm_cdr (desc);
    }

  return vec;
}

GridTile*
GridTileGenerator::create (const GridTileData& data)
{
  if (data.ur == GT_EMPTY || data.ul == GT_EMPTY || data.bl == GT_EMPTY || data.br == GT_EMPTY)
    {
      return 0;
    }

  // We switch to transparent when the tile has the same 'color' as the base ground
  // FIXME: ground color needs to be variable
  if (data.ur == GT_SAND && data.ul == GT_SAND && data.bl == GT_SAND && data.br == GT_SAND)
    {
      return 0;
    }

  TileTable::iterator i;
  for (i = tiles.begin (); i != tiles.end (); ++i)
    if (i->first == data)
      break;

  if (i != tiles.end ())
    {
      if (i->second.size () > 0)
	return (i->second)[rand () % (i->second.size ())]; // Return a random tile
      else
	{
	  // The tile list is empty, no tile available
          if (args->verbose)
            std::cout << "GridTileGenerator: Warning: Tile: " << data << " missing" << std::endl;
          return 0;
	}
    }
  else
    {
      std::cout << "GridTileGenerator: Warning: Tile: " << data << " missing" << std::endl;
      return emptytile;
    }
}

/* EOF */
