//  $Id: GameWorld.cxx,v 1.8 2002/03/31 20:43:43 sphair Exp $
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
#include "boost/smart_ptr.hpp"
#include "Mine.hxx"
#include "Tank.hxx"
#include "Projectile.hxx"
#include "Collideable.hxx"
#include "GameWorld.hxx"
#include "groundmap/GroundMapData.hxx"
#include "groundmap/GroundMap.hxx"
#include "GameObjData.hxx"
#include "buildings/BuildingMap.hxx"

GameWorld::GameWorld (const GameWorldData& data)
  : GameWorldData (data),
    current_time (0.0f)
{
  if (groundmap_data)
    groundmap = groundmap_data->create ();//this);

  if (buildingmap_data)
    buildingmap = buildingmap_data->create (this);

  if (!groundmap) 
    {
      std::cout << "GameWorld: No groundmap created, bailout" << std::endl;
      assert (groundmap);
    }
  
  if (!buildingmap)
    {
      std::cout << "GameWorld: No buildingmap created, bailout" << std::endl;
      assert (buildingmap);
    }

  objects.push_back (groundmap);
  objects.push_back (buildingmap);

  for (std::list<GameObjData*>::iterator i = gameobj_data.begin (); i != gameobj_data.end (); ++i)
    {
      objects.push_back ((*i)->create (this));
    }
}

GameWorld::GameWorld ()
{
}

GameWorld::~GameWorld ()
{
}

void 
GameWorld::add (GameObj* obj)
{
  objects.push_back(obj);
}

void 
GameWorld::add_front (GameObj* obj)
{
  objects.push_front (obj);
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
  objects.sort (z_pos_sorter ());
#endif

  for (ObjIter i = objects.begin (); 
       i != objects.end (); ++i)
    (*i)->draw (view);
  //for_each (objects.begin (), objects.end (), bind2nd(mem_fun (&GameObj::draw), view));
}

void 
GameWorld::draw_energie (View* view)
{
  for (ObjIter i = objects.begin (); 
       i != objects.end (); ++i)
    (*i)->draw_energie (view);
}

void
GameWorld::draw_levelmap (LevelMap* levelmap)
{
  //groundmap->draw_levelmap (levelmap);
  for (ObjIter i = objects.begin (); 
       i != objects.end (); ++i)
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

  //std::cout << "Number of GameObj's: " << objects.size () << "\r          " << std::flush;
#ifdef WIN32
  //std::remove_if doesn't seem to have any effect for gcc?! or
  //probally I just mixed true/false
  std::remove_if(objects.begin(), objects.end(), is_removable());
#else
  objects.remove_if(is_removable ()); 
#endif 

  for (ObjIter i = objects.begin ();
       i != objects.end (); ++i)
    (*i)->update (delta);
}

BuildingMap*
GameWorld::get_buildingmap ()
{
  return buildingmap;
}

GroundMap*
GameWorld::get_groundmap ()
{
  return groundmap;
}

/* EOF */
