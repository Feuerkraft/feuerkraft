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

#include <typeinfo>
#include <assert.h>
#include <iostream>
#include "guile.hpp"
#include "game_world.hpp"
#include "buildings/building_map_data.hpp"
#include "groundmap/ground_map_data.hpp"
#include "game_obj_data.hpp"
#include "groundmap/ground_map_data_factory.hpp"
#include "game_obj_data_factory.hpp"
#include "game_world_data.hpp"

GameWorldData::GameWorldData (SCM desc)
  : needs_delete (true)
{
  assert(scm_pair_p(desc));

  if (Guile::equal_p (scm_from_utf8_symbol ("feuerkraft-scenario"), scm_car(desc)))
    desc = scm_cdr(desc);
  else
    {
      std::cout << "File is not a feuerkraft scenario" << std::endl;
      assert(false);
    }

  while (scm_is_true(scm_pair_p(desc)))
    {
      if (scm_is_true(scm_pair_p (scm_car (desc))))
	{
	  SCM symbol = scm_caar(desc);
	  SCM data   = scm_cdar(desc);

	  if (scm_is_true(scm_symbol_p (symbol)))
	    {
	      if (Guile::equal_p (scm_from_utf8_symbol ("groundmap"), symbol))
		{
		  groundmap_data = GroundMapDataFactory::create (data);
		}
	      else if (Guile::equal_p (scm_from_utf8_symbol ("buildings"), symbol))
		{
		  buildingmap_data = new BuildingMapData (data);
		}
	      else if (Guile::equal_p (scm_from_utf8_symbol ("objects"), symbol))
		{
		  parse_objects(data);
		}
	      else if (Guile::equal_p (scm_from_utf8_symbol ("scripts"), symbol))
		{
		  parse_scripts(data);
		}
	      else
		{
		  std::cout << "GameWorldData: Error: " << symbol << " " << data << std::endl;;
		}
	    }
	  else
	    {
	      std::cout << "GameWorldData: Error not a symbol: ";// << symbol << " " << data << std::endl;;
	      scm_display(symbol, SCM_UNDEFINED);
              scm_newline(SCM_UNDEFINED);
	    }
	}
      else
	{
	  std::cout << "GameWorldData: Error not a pair: " << scm_car(desc) << std::endl;;
	}

      desc = scm_cdr(desc);
    }
}

void
GameWorldData::parse_objects (SCM desc)
{
  //std::cout << "GameWorldData::parse_objects" << std::endl;
  //scm_display (desc);
  //scm_newline ();
  while (scm_is_true(scm_pair_p(desc))) // is a list
    {
      if (scm_is_true(scm_pair_p (scm_car (desc)))) // is a symbol/value pair
	{
	  SCM symbol = scm_caar(desc);
	  SCM data   = scm_cdar(desc);

	  GameObjData* obj = GameObjDataFactory::create (symbol, data);
	  if (obj)
	    {
	      gameobj_data.push_back (obj);
	    }
	  else
	    {
	      std::cout << "Error: GameWorldData::parse_objects" << std::endl;
	    }
	}
      else
	{
	  std::cout << "Error: GameWorldData::parse_objects" << std::endl;
	}
      desc = scm_cdr (desc);
    }
}

GameWorldData::~GameWorldData ()
{
  if (needs_delete)
    {
      // FIXME: Memory Leak, we should clear the gameobj_data list here
    }
}

SCM
GameWorldData::dump_to_scm ()
{
  std::cout << "GameWorldData::dump_to_scm()" << std::endl;

  SCM world_lst = SCM_EOL;

  SCM objs = SCM_EOL;
  for (std::vector<GameObjData*>::iterator i = gameobj_data.begin (); i != gameobj_data.end (); ++i)
    {
      if (*i)
	{
	  SCM obj = (*i)->dump_to_scm ();
	  if (obj == SCM_BOOL_F)
	    {
	      std::cout << "GameWorldData: Error dumping: " << typeid(**i).name () << std::endl;
	    }
	  else // Object successfully dumped
	    {
	      objs = scm_cons (obj, objs);
	    }
	}
    }

  world_lst = scm_cons (scm_from_utf8_symbol ("objects"), scm_reverse(objs));

  world_lst = SCM_BOOL_F; //scm_listify (scm_from_utf8_symbol ("world"), world_lst, SCM_UNDEFINED);

  return world_lst;
}

void
GameWorldData::parse_scripts(SCM desc)
{
  while(!scm_is_true(scm_null_p(desc)))
    {
      SCM script = scm_car(desc);

      scripts.push_back(Guile::scm2string(script));

      desc = scm_cdr(desc);
    }
}

/* EOF */
