//  $Id: Ammotent.cc,v 1.3 2001/11/28 17:17:27 grumbel Exp $
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

#include "Vehicle.hh"
#include "Ammotent.hh"
#include <cmath>

extern CL_ResourceManager* resources;

Ammotent::Ammotent (boost::dummy_ptr<GameWorld> world, CL_Vector arg_pos)
  : GameObj (world),
    ammotent ("feuerkraft/ammotent", resources),
    pos (arg_pos)
{
}

Ammotent::~Ammotent ()
{
}

void 
Ammotent::draw (View* view)
{
  view->draw (ammotent, 
	      pos.x - 40,
	      pos.y - 75);
}

void 
Ammotent::update (float delta)
{
  std::list<boost::shared_ptr<GameObj> >& objs = world->get_objects ();

  for (GameWorld::ObjIter i = objs.begin (); i != objs.end (); ++i)
    {
      Vehicle* vehicle = dynamic_cast<Vehicle*>(i->get ());
      if (vehicle && fabs((vehicle->get_pos () - pos).norm ()) < 10)
	{
	  if (vehicle->get_velocity () == 0.0)
	    {
	      vehicle->reload_ammo (delta);
	    }
	}
    }
}

/* EOF */
