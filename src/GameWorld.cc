//  $Id: GameWorld.cc,v 1.5 2001/02/18 20:16:50 grumbel Exp $
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

static bool z_pos_sorter (boost::shared_ptr<GameObj> a, 
			  boost::shared_ptr<GameObj> b)
{
  return (a->get_z_pos () < b->get_z_pos ());
}

void 
GameWorld::draw ()
{
  objects.sort (z_pos_sorter);
  for (std::list<boost::shared_ptr<GameObj> >::iterator i = objects.begin (); 
       i != objects.end (); ++i)
    {
      (*i)->draw ();
    }
}

static bool is_removable (boost::shared_ptr<GameObj> obj)
{
  return obj->removable ();
}

void 
GameWorld::update ()
{
  //std::cout << "Number of GameObj's: " << objects.size () << "\r          " << std::flush;
  objects.remove_if(is_removable); 
  
  for (std::list<boost::shared_ptr<GameObj> >::iterator i = objects.begin ();
       i != objects.end (); ++i)
    (*i)->update ();
}

/* EOF */
