//  $Id: fuelstation.cpp,v 1.12 2003/06/22 18:34:52 grumbel Exp $
//
//  Feuerkraft - A Tank Battle Game
//  Copyright (C) 2000 Ingo Ruhnke <grumbel@gmx.de>
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//  
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//  
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include <cmath>
#include "../game_obj_manager.hpp"
#include "../color.hpp"
#include "../radar.hpp"
#include "../vehicles/vehicle.hpp"
#include "../resource_manager.hpp"
#include "../display/drawing_context.hpp"
#include "fuelstation.hpp"

Fuelstation::Fuelstation(const AList& lst)
  : Building(lst),
    fuelstation (resources->get_sprite("feuerkraft/fuelstation")),
    pos (x_pos * 40 + 40, y_pos * 40 + 60), // FIXME: Hardcoded tilesize
    refueling (false)
{
}

Fuelstation::~Fuelstation ()
{
}

void 
Fuelstation::draw (View& view)
{
  view.get_sc().color().draw(fuelstation, pos.x, pos.y);
  if (refueling)
    {
      view.get_sc().color().draw_fillrect(pos.x - 32, pos.y + 25,
                                  pos.x + 31, pos.y + 57,
                                  CL_Color(CL_Colorf(1.0, 1.0, 1.0,
                                                     sin(GameWorld::current()->get_time () * 10.0f)
                                                     * .3f + .5f)));
    }
}

void
Fuelstation::draw_radar (Radar& radar)
{
  radar.draw_blip (pos, 4, 0, 0, 1.0f);
}

void 
Fuelstation::update (float delta)
{
  delta *= 50;

  refueling = false;

  GameObjManager* objs = GameWorld::current()->get_game_obj_manager();
  for (GameObjManager::iterator i = objs->begin(); i != objs->end(); ++i)
    {
      Vehicle* vehicle = dynamic_cast<Vehicle*>(*i);
      if (vehicle && (vehicle->get_pos ().x > pos.x - 40
		      && vehicle->get_pos ().x < pos.x + 40
		      && vehicle->get_pos ().y > pos.y + 20
		      && vehicle->get_pos ().y < pos.y + 60))
	{
	  if (vehicle->get_velocity () == 0.0)
	    {
	      vehicle->refuel (delta);
	      refueling = true;
	    }
	}
    }
}

/* EOF */
