//  $Id: game_world.cxx,v 1.10 2003/05/13 17:30:27 grumbel Exp $
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

#include <algorithm>
#include <functional>

#include "mine.hxx"
#include "tank.hxx"
#include "projectile.hxx"
#include "collideable.hxx"
#include "game_world.hxx"
#include "groundmap/ground_map_data.hxx"
#include "groundmap/ground_map.hxx"
#include "game_obj.hxx"
#include "game_obj_data.hxx"
#include "game_obj_manager.hxx"
#include "view.hxx"
#include "trigger_manager.hxx"
#include "buildings/building_manager.hxx"
#include "buildings/building_map.hxx"

GameWorld* GameWorld::current_world = 0;

GameWorld::GameWorld()
{
}

GameWorld::GameWorld (const GameWorldData& data)
  : GameWorldData (data),
    game_obj_manager(new GameObjManager(this)),
    building_manager(new BuildingManager()),
    trigger_manager(new TriggerManager()),
    current_time (0.0f)
{
  current_world = this;
  
  if (groundmap_data)
    groundmap = groundmap_data->create ();//this);

  if (buildingmap_data)
    buildingmap = buildingmap_data->create();

  if (!groundmap) 
    {
      std::cout << "GameWorld: No groundmap created, bailout" << std::endl;
      assert(groundmap);
    }
  
  if (!buildingmap)
    {
      std::cout << "GameWorld: No buildingmap created, bailout" << std::endl;
      assert(buildingmap);
    }

  game_obj_manager->add_object(groundmap);
  game_obj_manager->add_object(buildingmap);

  for (std::vector<GameObjData*>::iterator i = gameobj_data.begin (); i != gameobj_data.end (); ++i)
    {
      game_obj_manager->add_object((*i)->create());
    }
  
  // FIXME: a little hacky
  //world_module = scm_c_define_module("feuerkraft game-world", 0, 0);
  //last_module  = scm_set_current_module(world_module);

  // Load scripts
  for(std::vector<std::string>::iterator i = scripts.begin(); i != scripts.end(); ++i)
    {
      std::cout << "### Loading Script: " << *i << std::endl;
      scm_c_primitive_load(i->c_str());
      std::cout << "### DONE: Loading Script: " << *i << std::endl;
    }
}

GameWorld::~GameWorld ()
{
  delete game_obj_manager;
  delete building_manager;
  delete trigger_manager;
  // FIXME: Memory Leak, we should clear the gameobj list here

  // Restore module FIXME: a little hacky
  //scm_set_current_module(last_module);
}

void 
GameWorld::add (GameObj* obj)
{
  game_obj_manager->add_object(obj);
}

void 
GameWorld::add_front (GameObj* obj)
{
  // FIXME: no go...
  game_obj_manager->add_object(obj);
}

struct z_pos_sorter
{
  bool operator() (GameObj* a, GameObj* b)
  {
    return a->get_z_pos () < b->get_z_pos ();
  }
};

// quicksort manual implementation, needed for msvc++'s sucky STL:
// (maybe we should move this into ClanLib/Core/Math)
// ---------------------------------------------------------------

template<class Container, class Iterator, class Pred>
void quicksort(Container &A, Iterator p, Iterator r, Pred &pred)
{
	while (p < r)
	{
		Iterator q = parition(A, p, r, pred);
		quicksort(A, p, q, pred);
		quicksort(A, q+1, r, pred);
	}
}

template<class Container, class Iterator, class Pred>
Iterator partition(Container &A, Iterator p, Iterator r, Pred &pred)
{
	Iterator x = p;
	Iterator i = p-1;
	Iterator j = r+1;

	while (true)
	{
		do --j; while (pred(*j, x));
		do ++i; while (pred(x, *j));

		if (i < j) A.swap(i, j);
		else return j;
	}
}

/*
template<class T, class Mem, class Arg>
class my_mem_fun 
{
public:
  void operator (T&) { }
}*/

void 
GameWorld::draw (View* view)
{
  //objects.sort (z_pos_sorter ());
#ifdef WIN32 // todo, change this define so that it checks STL library instead of platform.
//  if (!objects.empty()) quicksort(objects, objects.begin(), --objects.end(), z_pos_sorter ());
  objects.sort (z_pos_sorter ());
#else
  game_obj_manager->get_objects().sort (z_pos_sorter ());
#endif

  GameObjManager* objs = game_obj_manager;
  for (GameObjManager::iterator i = objs->begin(); i != objs->end(); ++i)
    {
      (*i)->draw (view);
    }
}

void 
GameWorld::draw_energie (View* view)
{
  GameObjManager* objs = game_obj_manager;
  for (GameObjManager::iterator i = objs->begin(); i != objs->end(); ++i)
    (*i)->draw_energie (view);
}

void
GameWorld::draw_levelmap (LevelMap* levelmap)
{
  //groundmap->draw_levelmap (levelmap);

  GameObjManager* objs = game_obj_manager;
  for (GameObjManager::iterator i = objs->begin(); i != objs->end(); ++i)
    (*i)->draw_levelmap (levelmap);
}

struct is_removable
{
  bool operator() (GameObj* obj)
  {
    return obj->removable ();
  }
};

void 
GameWorld::update (float delta)
{
  current_time += delta;

  trigger_manager->update(delta);

  game_obj_manager->get_objects().remove_if(is_removable ()); 

  GameObjManager* objs = game_obj_manager;
  for (GameObjManager::iterator i = objs->begin(); i != objs->end(); ++i)
    (*i)->update (delta);
}

BuildingMap*
GameWorld::get_buildingmap ()
{
  // FIXME: This is a ugly ugly hack...
  return dynamic_cast<BuildingMap*>(buildingmap);
}

GroundMap*
GameWorld::get_groundmap ()
{
  return groundmap;
}

GameObjManager*
GameWorld::get_game_obj_manager()
{
  return game_obj_manager;
}

/* EOF */
