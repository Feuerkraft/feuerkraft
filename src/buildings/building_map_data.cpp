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
#include "building_map_data.hpp"
#include "building_map.hpp"
#include "../guile.hpp"

BuildingMapData::BuildingMapData (SCM desc) :
  buildings_data(),
  width(),
  height()
{
  //std::cout << "BuildingMapData: parsing: start" << std::endl;

  // FIXME: Hardcoded is ugly!
  width = 256;
  height = 256;

  while (!scm_is_true(scm_null_p (desc)))
    {
      SCM symbol = scm_caar(desc);
      SCM data   = scm_cdar(desc);

      AList alst = Guile::scm2alist(data);
      std::string str = Guile::symbol2string(symbol);

      // FIXME: Should be placed in a BuildingDataFactory class
      buildings_data.push_back(BuildingData(str, alst));

      //std::cout << "BuildingData: " << str << "\n" << alst << std::endl;

      desc = scm_cdr(desc);
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
	  building_map_scm = scm_cons (obj, building_map_scm);
	}
    }

  building_map_scm = scm_cons(scm_from_utf8_symbol("buildingmap"), scm_reverse(building_map_scm));

  return building_map_scm;
#endif
}

/* EOF */
