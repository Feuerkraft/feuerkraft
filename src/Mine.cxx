//  $Id: Mine.cxx,v 1.4 2002/03/23 10:16:16 grumbel Exp $
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

#include "boost/smart_ptr.hpp"
#include "Tank.hxx"
#include "Mine.hxx"

extern SpriteProviderStorage* storage;
extern CL_ResourceManager* resources;

Mine::Mine (boost::dummy_ptr<GameWorld>  w, const CL_Vector& arg_pos) 
  : GameObj (w),
    sur ("feuerkraft/mine", resources),
    sur_active ("feuerkraft/mineactive", resources),
    pos (arg_pos),
    hole (storage->get ("feuerkraft/hole")),
    active (2),
    detonated (false)
{
}

void 
Mine::update (float delta) 
{
  if (!is_active ())
    {
      active -= delta;
    }
  else if (!detonated)
    {
      for (GameWorld::ObjIter j = world->get_objects ().begin ();
	   j != world->get_objects ().end (); ++j)
	{
	  Vehicle* vehicle = dynamic_cast<Vehicle*>(*j);

	  if (vehicle && (vehicle->get_pos () - get_pos ()).norm () < 30.0f)
	    {
	      detonate ();
	    }
	}
    }
}

bool 
Mine::is_active ()
{
  return (active <= 0);
}

void 
Mine::draw (View* view) 
{
  if (!is_active ())
    {
      view->draw (sur, int(pos.x - sur.get_width ()/2),
		  int(pos.y - sur.get_height ()/2));
    }
  else if (!detonated)
    {
      view->draw (sur_active, int(pos.x - sur.get_width ()/2),
		  int(pos.y - sur.get_height ()/2));
    }
  else
    {
      view->draw (hole, pos);
    }
}

void 
Mine::detonate () 
{
  for (GameWorld::ObjIter j = world->get_objects ().begin ();
       j != world->get_objects ().end (); ++j)
    {
      Vehicle* vehicle = dynamic_cast<Vehicle*>(*j);
      
      // If distance to the mine is smaller than 100 apply a force
      if (vehicle && (vehicle->get_pos () - get_pos ()).norm () < 100.0)
	{
	  CL_Vector force(pos - vehicle->get_pos ());
	  force = (100.0f) * (pos - vehicle->get_pos ()).norm ();
	  vehicle->collide (force);
	}
    }


  world->add (new Explosion (world, pos, Explosion::MEDIUM));
  detonated = true;
  //remove ();
}

/* EOF */
