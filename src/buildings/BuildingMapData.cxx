//  $Id: BuildingMapData.cxx,v 1.2 2002/03/17 12:01:58 grumbel Exp $
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
#include "TowerData.hxx"
#include "BuildingMapData.hxx"
#include "BuildingMap.hxx"

BuildingMapData::BuildingMapData (SCM desc)
{
  std::cout << "BuildingMapData: parsing: start" << std::endl;

  while (!gh_null_p (desc))
    {
      SCM symbol = gh_caar(desc);
      SCM data   = gh_cdar(desc);

      // FIXME: Should be placed in a BuildingDataFactory class
      if (gh_equal_p (gh_symbol2scm ("tower"), symbol))
	{
	  std::cout << "BuildingMapData: creating towerdata" << std::endl;
	  // building_data does not contain position information
	  buildings_data.push_back (new TowerData (data));
	}
      else
	{
	  std::cout << "BuildingMapData: Error: " << std::flush;
	  gh_display(symbol);
	  std::cout << std::endl;
	}

      desc = gh_cdr (desc);
    }

  std::cout << "BuildingMapData: parsing: stop" << std::endl;
}

BuildingMap*
BuildingMapData::create ()
{
  return new BuildingMap (*this);
}

/* EOF */
