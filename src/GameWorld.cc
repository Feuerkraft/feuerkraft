//  $Id: GameWorld.cc,v 1.13 2001/02/20 00:13:33 mbn Exp $
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
#include "Mine.hh"
#include "Tank.hh"
#include "Projectile.hh"
#include "Collideable.hh"
#include "GameWorld.hh"

GameWorld::GameWorld ()
{
}

GameWorld::~GameWorld ()
{
}

void 
GameWorld::add (boost::shared_ptr<GameObj> obj)
{
  obj->set_world (this);
  obj->init ();
  
  objects.push_back (obj);
}

void 
GameWorld::add (GameObj* obj)
{
  add (boost::shared_ptr<GameObj>(obj));
}

struct z_pos_sorter
{
  bool operator() (boost::shared_ptr<GameObj> a,
		   boost::shared_ptr<GameObj> b)
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

void 
GameWorld::draw ()
{
#ifdef WIN32 // todo, change this define so that it checks STL library instead of platform.
  if (!objects.empty()) quicksort(objects, objects.begin(), --objects.end(), z_pos_sorter ());
#else
  objects.sort (z_pos_sorter ());
#endif

  for (std::list<boost::shared_ptr<GameObj> >::iterator i = objects.begin (); 
       i != objects.end (); ++i)
    {
      (*i)->draw ();
    }
}

struct is_removable
{
  bool operator() (boost::shared_ptr<GameObj> obj)
  {
    return obj->removable ();
  }
};

void 
GameWorld::update ()
{
  //std::cout << "Number of GameObj's: " << objects.size () << "\r          " << std::flush;
//  objects.remove_if(is_removable ()); 
  std::remove_if(objects.begin(), objects.end(), is_removable());
  
  for (std::list<boost::shared_ptr<GameObj> >::iterator i = objects.begin ();
       i != objects.end (); ++i)
    (*i)->update ();
}

/* EOF */
