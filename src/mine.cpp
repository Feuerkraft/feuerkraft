//  $Id: mine.cpp,v 1.11 2003/06/20 20:54:23 grumbel Exp $
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

#include "alist.hpp"
#include "vehicles/tank.hpp"
#include "mine.hpp"
#include "game_obj_manager.hpp"
#include "game_world.hpp"
#include "groundmap/ground_map.hpp"
#include "collision_manager.hpp"
#include "property_set.hpp"
#include "resource_manager.hpp"

Mine::Mine (const AList& lst)
  : pos (0, 0),
    active (2),
    detonated (false),
    hole (resources->get_sprite ("feuerkraft/hole"))
{
  properties->register_float("x-pos", &pos.x);
  properties->register_float("y-pos", &pos.y);
  
  pos.x = lst.get_float("x-pos");
  pos.y = lst.get_float("y-pos");

  GroundType type = GameWorld::current()->get_groundmap ()->get_groundtype (pos.x, pos.y);
  if (type == GT_FLATWATER)
    {
      sur = resources->get_sprite ("feuerkraft/minewater");
      sur_active = resources->get_sprite ("feuerkraft/minewateractive");
    }
  else if (type == GT_DEEPWATER)
    {
      sur = resources->get_sprite ("feuerkraft/minewater");
      sur_active = resources->get_sprite ("feuerkraft/minewateractive");
      remove (); // Mines can't be placed in deepwater
    }
  else
    {
      sur = resources->get_sprite ("feuerkraft/mine");
      sur_active = resources->get_sprite ("feuerkraft/mineactive");
    }
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
      CollisionManager::current()->add_circle(get_id(), pos.x, pos.y, 8);
    }
}

void
Mine::on_collision(GameObj* obj)
{
  Mine::detonate();
}

bool 
Mine::is_active ()
{
  return (active <= 0);
}

void 
Mine::draw (View& view) 
{
  if (!is_active ())
    {
      view.get_sc().color().draw(sur, pos.x, pos.y);
    }
  else if (!detonated)
    {
      view.get_sc().color().draw(sur_active, pos.x, pos.y);
    }
  else
    {
      //view->draw (hole, pos);
    }
}

void 
Mine::detonate () 
{
  // Search for game objects in the given area to make damage
  GameObjManager* objs = GameWorld::current()->get_game_obj_manager();
  for (GameObjManager::iterator i = objs->begin(); i != objs->end(); ++i)
    {
      //Vehicle* vehicle = dynamic_cast<Vehicle*>(*i);
      
      // If distance to the mine is smaller than 100 apply a force
      /*if (vehicle && (vehicle->get_pos () - get_pos ()).get_length() < 100.0)
	{
	  FloatVector2d force(pos - vehicle->get_pos());
	  force = (100.0f) * (pos - vehicle->get_pos()).get_length();
	  vehicle->collide(force);
	}*/
    }

  GameWorld::current()->add (new Explosion(pos, Explosion::MEDIUM));
  detonated = true;
  //remove ();
}

/* EOF */
