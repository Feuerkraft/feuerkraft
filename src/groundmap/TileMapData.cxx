//  $Id: TileMapData.cxx,v 1.2 2002/03/09 14:53:51 grumbel Exp $
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
#include "TileDataFactory.hxx"
#include "TileMapData.hxx"
#include "TileMap.hxx"

TileMapData::TileMapData (SCM desc)
{
  width = -1;
  height = -1;

  while (!gh_null_p (desc))
    {
      SCM symbol = gh_caar(desc);
      SCM data   = gh_cdar(desc);

      if (gh_equal_p (gh_symbol2scm ("width"), symbol))
	{
	  width = gh_scm2int(gh_car (data));
	}
      else if (gh_equal_p (gh_symbol2scm ("height"), symbol))
	{
	  height = gh_scm2int(gh_car (data));
	}
      else if (gh_equal_p (gh_symbol2scm ("tiles"), symbol))
	{
	  assert (width != -1);
	  assert (height != -1);

	  tiles_data.resize (width * height);

	  for (std::vector<TileData*>::iterator i = tiles_data.begin ();
	       i != tiles_data.end (); ++i)
	    *i = NULL;

	  parse_tiles (data);
	}
      else
	{
	  std::cout << "TileMapData: Unknown data type: '" << std::flush;
	  gh_display (symbol);
	  std::cout << "' with data: " << std::flush;
	  gh_display (data);
	  std::cout << std::endl;
	  return;
	}

      desc = gh_cdr (desc);
    }
}

TileMapData::~TileMapData ()
{ 
}

void
TileMapData::parse_tiles (SCM desc)
{
  int i = 0;
  while (!gh_null_p (desc))
    {
      if (i < tiles_data.size ())
	{
	  tiles_data[i] = TileDataFactory::create (gh_car(desc));
	  ++i;
	}
      else
	{
	  std::cout << "To many tiles...." << std::endl;
	}
      
      desc = gh_cdr (desc);
    }
}

GroundMap*
TileMapData::create ()
{
  return new TileMap (*this);
}

/* EOF */
