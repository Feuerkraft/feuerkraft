//  $Id: game_world.cxx,v 1.4 2003/05/02 14:28:26 grumbel Exp $
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
#include "timed_trigger_manager.hxx"
#include "buildings/building_map.hxx"

GameWorld::GameWorld (const GameWorldData& data)
  : GameWorldData (data),
    game_obj_manager(new GameObjManager(this)),
    timed_trigger_manager(new TimedTriggerManager()),
    current_time (0.0f)
{
  if (groundmap_data)
    groundmap = groundmap_data->create ();//this);

  if (buildingmap_data)
    buildingmap = buildingmap_data->create (this);

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

  for (std::list<GameObjData*>::iterator i = gameobj_data.begin (); i != gameobj_data.end (); ++i)
    {
      game_obj_manager->add_object((*i)->create (this));
    }
}

GameWorld::~GameWorld ()
{
  delete game_obj_manager;
  delete timed_trigger_manager;
  // FIXME: Memory Leak, we should clear the gameobj list here
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

  timed_trigger_manager->update(delta);

  game_obj_manager->get_objects().remove_if(is_removable ()); 

  GameObjManager* objs = game_obj_manager;
  for (GameObjManager::iterator i = objs->begin(); i != objs->end(); ++i)
    (*i)->update (delta);

  // FIXME: insert collision check here

  for (GameObjManager::iterator i = objs->begin(); i != objs->end(); ++i)
    (*i)->flip ();
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

GameWorldData*
GameWorld::get_data ()
{
  std::cout << "GameWorld::get_data()" << std::endl;
  // Clear the current GameObjData data list
  if (needs_delete)
    {
      std::cout << "GameWorld: Deleting current data objects" << std::endl;
      for (std::list<GameObjData*>::iterator i = gameobj_data.begin (); i != gameobj_data.end (); ++i)
	delete *i;
      gameobj_data.clear ();
      needs_delete = false;
    }
  
  // Fill the data object with the current gameobj's and sync them
  GameObjManager* objs = game_obj_manager;
  for (GameObjManager::iterator i = objs->begin(); i != objs->end(); ++i)
    gameobj_data.push_back ((*i)->get_data ());
  
  // groundmap_data is constant => no sync required
  
  buildingmap_data =  dynamic_cast<BuildingMapData*>(buildingmap->get_data ());

  return this;
}

GameObjManager*
GameWorld::get_game_obj_manager()
{
  return game_obj_manager;
}

/* EOF */
