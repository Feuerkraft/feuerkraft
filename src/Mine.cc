//  $Id: Mine.cc,v 1.5 2001/05/01 15:06:52 grumbel Exp $
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
#include "Tank.hh"
#include "Mine.hh"

Mine::Mine (boost::dummy_ptr<GameWorld>  w, const CL_Vector& arg_pos) 
  : GameObj (w),
    sur ("feuerkraft/mine", resources),
    sur_active ("feuerkraft/mineactive", resources),
    pos (arg_pos),
    active (50)
{
}

void 
Mine::update (float delta) 
{
  if (!is_active ())
    {
      --active;
    }
  else
    {
      for (std::list<boost::shared_ptr<GameObj> >::iterator 
	     j = world->get_objects ().begin ();
	   j != world->get_objects ().end (); ++j)
	{
	  Vehicle* vehicle = dynamic_cast<Vehicle*>(j->get());

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
      sur.put_screen (pos.x - sur.get_width ()/2,
		      pos.y - sur.get_height ()/2);
    }
  else
    {
      sur_active.put_screen (pos.x - sur.get_width ()/2,
			     pos.y - sur.get_height ()/2);
    }
}

void 
Mine::detonate () 
{
  for (std::list<boost::shared_ptr<GameObj> >::iterator 
	 j = world->get_objects ().begin ();
       j != world->get_objects ().end (); ++j)
    {
      Vehicle* vehicle = dynamic_cast<Vehicle*>(j->get());
      
      // If distance to the mine is smaller than 100 apply a force
      if (vehicle && (vehicle->get_pos () - get_pos ()).norm () < 100.0)
	{
	  CL_Vector force(pos - vehicle->get_pos ());
	  force = (100.0f) * (pos - vehicle->get_pos ()).norm ();
	  vehicle->collide (force);
	}
    }


  world->add (boost::shared_ptr<GameObj>(new Explosion (world, pos, Explosion::MEDIUM)));
  remove ();
}

/* EOF */
