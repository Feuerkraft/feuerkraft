//  $Id: TileMapData.cxx,v 1.4 2002/03/18 10:46:32 sphair Exp $
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
	  parse_tiles (data);
	}
      else if (gh_equal_p (gh_symbol2scm ("map"), symbol))
	{
	  parse_map (data);
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
TileMapData::parse_map (SCM desc)
{
  assert (width != -1);
  assert (height != -1);
  tilemap_data.resize (width * height);
  
  // Init the map to '0'
  for (std::vector<int>::iterator it = tilemap_data.begin ();
       it != tilemap_data.end (); ++it)
    *it = 0;
  
  std::cout << "Tilemap MapData: " << std::flush;
  gh_display (desc);
  gh_newline ();
  
  int i = 0;
  while (!gh_null_p (desc))
    {
      if (i < tilemap_data.size())
	{
	  tilemap_data[i] = gh_scm2int (gh_car (desc));
	  ++i;
	}
      else
	{
	  std::cout << "TileMapData: map to large" << std::endl;
	}
      
      desc = gh_cdr(desc);
    }
}

void
TileMapData::parse_tiles (SCM desc)
{
  //std::cout << "TileMapData::parse_tiles: " tiles_ << std::endl;
  while (!gh_null_p (desc))
    {
      tiles_data.push_back (TileDataFactory::create (gh_car(desc)));
      desc = gh_cdr (desc);
    }
}

GroundMap*
TileMapData::create ()
{
  return new TileMap (*this);
}

/* EOF */
