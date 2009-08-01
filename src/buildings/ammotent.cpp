//  $Id: ammotent.cpp,v 1.12 2003/06/22 18:34:52 grumbel Exp $
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

#include <math.h>
#include "../color.hpp"
#include "../game_obj_manager.hpp"
#include "../radar.hpp"
#include "../resource_manager.hpp"
#include "../vehicles/vehicle.hpp"
#include "../display/drawing_context.hpp"
#include "ammotent.hpp"

Ammotent::Ammotent (const AList& lst)
  : Building (lst),
    ammotent (resources->get_sprite("feuerkraft/ammotent")),
    pos (x_pos * 40 + 40, y_pos * 40 + 60), // FIXME: Hard coded tilesize again...
    reloading(false)
{
}

Ammotent::~Ammotent ()
{
}

void 
Ammotent::draw (View& view)
{
  view.get_sc().color().draw(ammotent, pos.x, pos.y);
  if (reloading)
    {
      view.get_sc().color().draw_fillrect(pos.x - 32, pos.y + 25,
                                  pos.x + 31, pos.y + 57,
                                  CL_Color(CL_Colorf(1.0f, 1.0f, 1.0f, 
                                                     sin(GameWorld::current()->get_time () * 10.0f)
                                                     * .3f + .5f)));
    }
}

void
Ammotent::draw_radar (Radar& radar)
{
  radar.draw_blip (pos, 4, 0, 0, 1.0f);
}

void 
Ammotent::update (float delta)
{
  delta *= 50;

  reloading = false;

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
	      vehicle->reload_ammo (delta);
	      reloading = true;
	    }
	}
    }
}

/* EOF */
