//  $Id: BuildingMapData.cxx,v 1.4 2002/03/23 12:20:43 grumbel Exp $
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
#include "BuildingMapData.hxx"
#include "BuildingMap.hxx"

#include "TowerData.hxx"
#include "FuelstationData.hxx"
#include "AmmotentData.hxx"
#include "BaseData.hxx"
#include "HeadquarterData.hxx"

BuildingMapData::BuildingMapData (SCM desc)
{
  std::cout << "BuildingMapData: parsing: start" << std::endl;

  width = 100;
  height = 100;

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
      else if (gh_equal_p (gh_symbol2scm ("ammotent"), symbol))
	{
	  std::cout << "BuildingMapData: creating ammotent" << std::endl;
	  buildings_data.push_back (new AmmotentData (data));
	}
      else if (gh_equal_p (gh_symbol2scm ("fuelstation"), symbol))
	{
	  std::cout << "BuildingMapData: creating ammotent" << std::endl;
	  buildings_data.push_back (new FuelstationData (data));
	}
      else if (gh_equal_p (gh_symbol2scm ("headquarter"), symbol))
	{
	  std::cout << "BuildingMapData: creating headquarter" << std::endl;
	  buildings_data.push_back (new HeadquarterData (data));
	}
      else if (gh_equal_p (gh_symbol2scm ("base"), symbol))
	{
	  std::cout << "BuildingMapData: creating base" << std::endl;
	  buildings_data.push_back (new BaseData (data));
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
BuildingMapData::create (boost::dummy_ptr<GameWorld> world)
{
  return new BuildingMap (world, *this);
}

/* EOF */
