//  $Id: ground_map_data_factory.cxx,v 1.2 2003/04/19 23:17:53 grumbel Exp $
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
#include "tile_map_data.hxx"
#include "multi_ground_map.hxx"
#include "grid_map_data.hxx"
#include "ground_map_data_factory.hxx"

GroundMapData* 
GroundMapDataFactory::create (SCM desc)
{
  MultiGroundMapData* multigroundmap = new MultiGroundMapData ();

  /*std::cout << "GroundMapFactory: desc: "<< std::flush;
  gh_display (desc);
  gh_newline ();*/

  while (gh_pair_p (desc))
    {
      SCM symbol = gh_caar (desc);
      SCM data   = gh_cdar (desc);

      /*      
      std::cout << "GroundMapFactory: symbol: "<< std::flush;
      gh_display (symbol);
      gh_newline ();
      
      std::cout << "GroundMapFactory: data: "<< std::flush;
      gh_display (data);
      gh_newline ();
      */
      if (gh_equal_p (gh_symbol2scm ("tilemap"), symbol))
	{
	  multigroundmap->add(new TileMapData (data));
	}
      else if (gh_equal_p (gh_symbol2scm ("gridmap"), symbol))
	{
	  multigroundmap->add(new GridMapData (data));
	}
      else
	{
	  std::cout << "GroundMapFactory: Unknown map type: " << std::flush;
	  gh_display (symbol);
	  gh_newline ();
	  //return 0;
	}

      desc = gh_cdr (desc);
    }

  return multigroundmap;
}

/* EOF */
