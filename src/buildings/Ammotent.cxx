//  $Id: Ammotent.cxx,v 1.4 2002/03/26 16:46:36 grumbel Exp $
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
#include "../Radar.hxx"
#include "Ammotent.hxx"
#include "../Vehicle.hxx"

extern SpriteProviderStorage* storage;
extern CL_ResourceManager* resources;

Ammotent::Ammotent (boost::dummy_ptr<GameWorld> world, const AmmotentData& data)
  : Building (world),
    AmmotentData (data),
    ammotent (storage->get("feuerkraft/ammotent")),
    pos (data.x_pos * 40 + 40, data.y_pos * 40 + 60), // FIXME: Hard coded tilesize again...
    reloading(false)
{
}

Ammotent::~Ammotent ()
{
}

void 
Ammotent::draw (boost::dummy_ptr<View> view)
{
  view->draw (&ammotent, pos);
  if (reloading)
    {
      view->draw_fillrect(int(pos.x - 32), int (pos.y + 25),
			  int(pos.x + 31), int (pos.y + 57),
			  1.0, 1.0, 1.0, sin(get_world ()->get_time () * 10.0f) * .3f + .5f);
    }
}

void
Ammotent::draw_radar (boost::dummy_ptr<Radar> radar)
{
  radar->draw_blip (pos, 4);
}

void 
Ammotent::update (float delta)
{
  delta *= 50;
  std::list<GameObj*>& objs = get_world ()->get_objects ();

  reloading = false;

  for (GameWorld::ObjIter i = objs.begin (); i != objs.end (); ++i)
    {
      Vehicle* vehicle = dynamic_cast<Vehicle*>(*i);
      if (vehicle && (vehicle->get_pos ().x > pos.x - 40
		      && vehicle->get_pos ().x < pos.x + 40
		      && vehicle->get_pos ().y > pos.y + 20
		      && vehicle->get_pos ().y < pos.y + 60))
	{
	  if (vehicle->get_velocity () == 0.0)
	    {
	      vehicle->reload_ammo (delta);
	      reloading = true;
	    }
	}
    }
}

/* EOF */
