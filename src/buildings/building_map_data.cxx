//  $Id: building_map_data.cxx,v 1.6 2003/06/22 19:22:56 grumbel Exp $
//
//  Feuerkraft - A Tank Battle Game
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
#include "../guile.hxx"

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

      AList alst = Guile::scm2alist(data);
      std::string str = Guile::symbol2string(symbol);

      // FIXME: Should be placed in a BuildingDataFactory class
      buildings_data.push_back(BuildingData(str, alst));

      std::cout << "BuildingData: " << str << "\n" << alst << std::endl;

      desc = gh_cdr(desc);
    }
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
  return SCM_EOL;
#if 0
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
#endif
}

/* EOF */
