//  $Id: Fuelstation.cxx,v 1.2 2002/03/17 17:10:45 grumbel Exp $
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
#include "Fuelstation.hxx"
#include "../Vehicle.hxx"

extern SpriteProviderStorage* storage;
extern CL_ResourceManager* resources;

Fuelstation::Fuelstation (boost::dummy_ptr<GameWorld> world, const FuelstationData& data)
  : Building (world),
    FuelstationData (data),
    fuelstation (storage->get("feuerkraft/fuelstation")),
    pos (x_pos * 40 + 40, y_pos * 40 + 60) // FIXME: Hardcoded tilesize
{
}

Fuelstation::~Fuelstation ()
{
}

void 
Fuelstation::draw (boost::dummy_ptr<View> view)
{
  view->draw (&fuelstation, pos);
}

void 
Fuelstation::update (float delta)
{
  delta *= 50;

  //FIXME: Slow
  std::list<boost::shared_ptr<GameObj> >& objs = get_world ()->get_objects ();

  for (GameWorld::ObjIter i = objs.begin (); i != objs.end (); ++i)
    {
      Vehicle* vehicle = dynamic_cast<Vehicle*>(i->get ());
      if (vehicle && fabs((vehicle->get_pos () - pos).norm ()) < 10)
	{
	  if (vehicle->get_velocity () == 0.0)
	    {
	      vehicle->refuel (delta);
	    }
	}
    }
}

/* EOF */
