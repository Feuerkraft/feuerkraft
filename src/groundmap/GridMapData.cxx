//  $Id: GridMapData.cxx,v 1.2 2002/03/25 15:32:58 grumbel Exp $
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
#include <ClanLib/png.h>
#include "GridMap.hxx"
#include "GridMapData.hxx"

GridMapData::GridMapData (SCM desc)
{
  grid_width  = -1;
  grid_height = -1;
  
  while (!gh_null_p (desc))
    {
      SCM symbol = gh_caar(desc);
      SCM data   = gh_cdar(desc);

      if (gh_equal_p (gh_symbol2scm ("file"), symbol))
	{
	  parse_from_file (data);
	}
      else
	{
	  std::cout << "GridMapData: Unknown data type: '" << std::flush;
	  gh_display (symbol);
	  std::cout << "' with data: " << std::flush;
	  gh_display (data);
	  std::cout << std::endl;
	  return;
	}

      desc = gh_cdr (desc);
    }
}

GridMapData::~GridMapData ()
{
}

void
GridMapData::parse_from_file (SCM desc)
{
  char* str = gh_scm2newstr(gh_car (desc), 0);
  std::cout << "Loading from: " << str << std::endl;
  std::string filename = str;
  free (str);
  
  CL_PNGProvider provider(filename);

  provider.lock ();
  assert (provider.is_indexed ());

  grid_width  = provider.get_width ();
  grid_height = provider.get_height ();

  grid_data.resize (grid_width * grid_height);
  
  unsigned char* buffer = static_cast<unsigned char*>(provider.get_data ());
  for (int i = 0; i < grid_width * grid_height; ++i)
    grid_data[i] = static_cast<GroundType>(buffer[i]);

  provider.unlock (); 
}

GroundMap*
GridMapData::create ()
{
  return new GridMap (*this);
}

/* EOF */
