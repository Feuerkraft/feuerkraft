//  $Id: Fuelstation.cc,v 1.2 2001/05/05 13:40:48 grumbel Exp $
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

#include <cmath>
#include "Vehicle.hh"
#include "Fuelstation.hh"

extern CL_ResourceManager* resources;

Fuelstation::Fuelstation (boost::dummy_ptr<GameWorld> world, CL_Vector arg_pos)
  : GameObj (world),
    fuelstation ("feuerkraft/fuelstation", resources),
    pos (arg_pos)
{
}

Fuelstation::~Fuelstation ()
{
}

void 
Fuelstation::draw (View* view)
{
  view->draw (fuelstation, 
	      pos.x - 40,
	      pos.y - 75);
}

void 
Fuelstation::update (float delta)
{
  //FIXME: Slow
  std::list<boost::shared_ptr<GameObj> >& objs = world->get_objects ();

  for (GameWorld::ObjIter i = objs.begin (); i != objs.end (); ++i)
    {
      Vehicle* vehicle = dynamic_cast<Vehicle*>(i->get ());
      if (vehicle && std::fabs((vehicle->get_pos () - pos).norm ()) < 10)
	{
	  if (vehicle->get_velocity () == 0.0)
	    {
	      vehicle->refuel (delta);
	    }
	}
    }
}

/* EOF */
