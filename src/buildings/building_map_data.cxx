//  $Id: building_map_data.cxx,v 1.3 2003/05/11 11:20:45 grumbel Exp $
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
#include "building_map_data.hxx"
#include "building_map.hxx"

#include "tower_data.hxx"
#include "fuelstation_data.hxx"
#include "ammotent_data.hxx"
#include "base_data.hxx"
#include "headquarter_data.hxx"
#include "wall.hxx"
#include "wall_door.hxx"

BuildingMapData::BuildingMapData (SCM desc)
{
  //std::cout << "BuildingMapData: parsing: start" << std::endl;

  // FIXME: Hardcoded is ugly!
  width = 256;
  height = 256;

  while (!gh_null_p (desc))
    {
      SCM symbol = gh_caar(desc);
      SCM data   = gh_cdar(desc);

      // FIXME: Should be placed in a BuildingDataFactory class
      if (gh_equal_p (gh_symbol2scm ("tower"), symbol))
	{
	  //std::cout << "BuildingMapData: creating towerdata" << std::endl;
	  // building_data does not contain position information
	  buildings_data.push_back(new TowerData (data));
	}
      else if (gh_equal_p (gh_symbol2scm ("ammotent"), symbol))
	{
	  //std::cout << "BuildingMapData: creating ammotent" << std::endl;
	  buildings_data.push_back(new AmmotentData (data));
	}
      else if (gh_equal_p (gh_symbol2scm ("wall"), symbol))
	{
	  buildings_data.push_back(new WallData (data));
	}
      else if (gh_equal_p (gh_symbol2scm ("fuelstation"), symbol))
	{
	  //std::cout << "BuildingMapData: creating ammotent" << std::endl;
	  buildings_data.push_back(new FuelstationData (data));
	}
      else if (gh_equal_p (gh_symbol2scm ("headquarter"), symbol))
	{
	  //std::cout << "BuildingMapData: creating headquarter" << std::endl;
	  buildings_data.push_back(new HeadquarterData (data));
	}
      else if (gh_equal_p (gh_symbol2scm ("base"), symbol))
	{
	  buildings_data.push_back(new BaseData (data));
	}
      else if (gh_equal_p (gh_symbol2scm ("walldoor"), symbol))
	{
	  buildings_data.push_back(new WallDoorData (data));
	}
      else
	{
	  std::cout << "BuildingMapData: Error: " << std::flush;
	  gh_display(symbol);
	  std::cout << std::endl;
	}

      desc = gh_cdr (desc);
    }

  //std::cout << "BuildingMapData: parsing: stop" << std::endl;
}

BuildingMapData::~BuildingMapData ()
{
}

GameObj*
BuildingMapData::create ()
{
  return new BuildingMap(*this);
}

SCM
BuildingMapData::dump_to_scm ()
{
  SCM building_map_scm = SCM_EOL;
  for (std::vector<BuildingData*>::iterator i = buildings_data.begin ();
       i != buildings_data.end (); ++i)
    {
      SCM obj = (*i)->dump_to_scm ();

      if (obj == SCM_BOOL_F)
	{
	  std::cout << "BuildingMapData: Error dumping: " << typeid(**i).name () << std::endl;
	}
      else // dump successful
	{
	  building_map_scm = gh_cons (obj, building_map_scm);
	}
    }

  building_map_scm = gh_cons (gh_symbol2scm ("buildingmap"), gh_reverse (building_map_scm));

  return building_map_scm;
}

/* EOF */
