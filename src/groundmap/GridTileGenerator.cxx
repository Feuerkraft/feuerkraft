//  $Id: GridTileGenerator.cxx,v 1.3 2002/03/27 13:40:13 grumbel Exp $
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

#include <iostream>
#include "GridTile.hxx"
#include "GridTileGenerator.hxx"

GridTileGenerator::GridTileGenerator (std::string filename)
  : emptytile (new GridTile ("feuerkraft/emptytile"))
{
  SCM fdes = scm_open_file (gh_str02scm(filename.c_str ()), 
			    gh_str02scm("r"));
  SCM lst  = scm_read (fdes);

  lst = gh_cdr(lst); // Skip the 'tiles' mark

  while (gh_pair_p(lst))
    {
      parse_line (gh_car (lst));
      lst = gh_cdr(lst); 
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
  SCM data = gh_car (desc);
  SCM lst  = gh_cdr (desc);

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
  data.ul = symbol2GroundType(gh_car (desc));
  data.ur = symbol2GroundType(gh_cadr (desc));
  data.br = symbol2GroundType(gh_caddr (desc));
  data.bl = symbol2GroundType(gh_car(gh_cdddr (desc)));
  
  return data;
}

GroundType
GridTileGenerator::symbol2GroundType (SCM symbol)
{
  if (gh_equal_p (gh_symbol2scm ("s"), symbol))
    {
      return GT_SAND;
    }
  else if (gh_equal_p (gh_symbol2scm ("f"), symbol))
    {
      return GT_FLATWATER;
    }
  else if (gh_equal_p (gh_symbol2scm ("d"), symbol))
    {
      return GT_DEEPWATER;
    }
  else if (gh_equal_p (gh_symbol2scm ("g"), symbol))
    {
      return GT_GRASS;
    }
  else if (gh_equal_p (gh_symbol2scm ("m"), symbol))
    {
      return GT_MUD;
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

  while (gh_pair_p(desc))
    {
      char* str = gh_scm2newstr (gh_car (desc), 0);
      vec.push_back (new GridTile (str));
      
      free (str);
      desc = gh_cdr (desc);
    }

  return vec;
}

GridTile*
GridTileGenerator::create (const GridTileData& data)
{
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
	  // The tile list is empty
	  return emptytile;
	}
    }
  else
    {
      // We don't have a tiledesc entry for this tile
      return emptytile;
    }
}

/* EOF */
