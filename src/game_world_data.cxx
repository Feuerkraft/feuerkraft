//  $Id: game_world_data.cxx,v 1.4 2003/05/18 14:00:07 grumbel Exp $
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
#include "guile.hxx"
#include "game_world.hxx"
#include "buildings/building_map_data.hxx"
#include "groundmap/ground_map_data.hxx"
#include "game_obj_data.hxx"
#include "groundmap/ground_map_data_factory.hxx"
#include "game_obj_data_factory.hxx"
#include "game_world_data.hxx"

GameWorldData::GameWorldData ()
  : needs_delete (false)
{
}

GameWorldData::GameWorldData (SCM desc)
  : needs_delete (true)
{
  assert(gh_pair_p(desc));

  if (gh_equal_p (gh_symbol2scm ("feuerkraft-scenario"), gh_car(desc)))
    desc = gh_cdr(desc);
  else
    {
      std::cout << "File is not a feuerkraft scenario" << std::endl;
      assert(false);
    }

  while (gh_pair_p(desc))
    {
      if (gh_pair_p (gh_car (desc)))
	{
	  SCM symbol = gh_caar(desc);
	  SCM data   = gh_cdar(desc);   

	  if (gh_symbol_p (symbol))
	    {
	      if (gh_equal_p (gh_symbol2scm ("groundmap"), symbol))
		{
		  groundmap_data = GroundMapDataFactory::create (data);
		}
	      else if (gh_equal_p (gh_symbol2scm ("buildings"), symbol)) 
		{
		  buildingmap_data = new BuildingMapData (data);
		}
	      else if (gh_equal_p (gh_symbol2scm ("objects"), symbol))
		{
		  parse_objects(data);
		}
	      else if (gh_equal_p (gh_symbol2scm ("scripts"), symbol))
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
	      gh_display (symbol); gh_newline ();
	    }
	}
      else
	{
	  std::cout << "GameWorldData: Error not a pair: " << gh_car(desc) << std::endl;;
	}

      desc = gh_cdr(desc);
    }
}

void
GameWorldData::parse_objects (SCM desc)
{
  //std::cout << "GameWorldData::parse_objects" << std::endl;
  //gh_display (desc);
  //gh_newline ();
  while (gh_pair_p(desc)) // is a list
    {
      if (gh_pair_p (gh_car (desc))) // is a symbol/value pair
	{
	  SCM symbol = gh_caar(desc);
	  SCM data   = gh_cdar(desc);   

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
      desc = gh_cdr (desc);
    }
}

GameWorldData::~GameWorldData ()
{
  if (needs_delete)
    {
      // FIXME: Memory Leak, we should clear the gameobj_data list here
    }
}

GameWorld*
GameWorldData::create ()
{
  return new GameWorld (*this);
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
	      objs = gh_cons (obj, objs);
	    }
	}
    }
  
  world_lst = gh_cons (gh_symbol2scm ("objects"), gh_reverse(objs));

  world_lst = SCM_BOOL_F; //scm_listify (gh_symbol2scm ("world"), world_lst, SCM_UNDEFINED);

  return world_lst;
}

void
GameWorldData::parse_scripts(SCM desc)
{
  while(!gh_null_p(desc))
    {
      SCM script = gh_car(desc);

      scripts.push_back(Guile::scm2string(script));
      
      desc = gh_cdr(desc);
    }
}

/* EOF */
