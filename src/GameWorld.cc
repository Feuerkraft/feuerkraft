//  $Id: GameWorld.cc,v 1.2 2001/02/18 00:49:16 grumbel Exp $
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
GameWorld::add (GameObj* obj)
{
  obj->set_world (this);

  objects.push_back (obj);
}

static bool z_pos_sorter (GameObj* a, GameObj* b)
{
  return (a->get_z_pos () < b->get_z_pos ());
}

void 
GameWorld::draw ()
{
  objects.sort (z_pos_sorter);
  for (std::list<GameObj*>::iterator i = objects.begin (); 
       i != objects.end (); ++i)
    {
      (*i)->draw ();
    }
}

static bool is_removable (GameObj* obj)
{
  return obj->removable ();
}

void 
GameWorld::update ()
{
  //std::cout << "Number of GameObj's: " << objects.size () << "\r          " << std::flush;
  objects.remove_if(is_removable); 
  
  for (std::list<GameObj*>::iterator i = objects.begin ();
       i != objects.end (); ++i)
    (*i)->update ();

  // Check for collision
  for (std::list<GameObj*>::iterator i = objects.begin ();
       i != objects.end (); ++i)
    {
      Projectile* projectile = dynamic_cast<Projectile*>(*i);
      if (projectile)
	{
	  for (std::list<GameObj*>::iterator j = objects.begin ();
	       j != objects.end (); ++j)
	    {
	      Collideable* collideable = dynamic_cast<Collideable*>(*j);
	      if (collideable)
		{
		  if ((collideable)->is_colliding (projectile->get_pos ()))
		    {
		      collideable->collide (projectile);
		    }
		}
	    }
	}

      Mine* mine = dynamic_cast<Mine*>(*i);
      if (mine)
	{
	  for (std::list<GameObj*>::iterator j = objects.begin ();
	       j != objects.end (); ++j)
	    {
	      Tank* tank = dynamic_cast<Tank*>(*j);
	      if (tank && (tank->get_pos () - mine->get_pos ()).norm () < 20.0)
		{
		  mine->detonate ();
		}
	    }	  
	}
    }
}

/* EOF */
