//  $Id: mine.cxx,v 1.4 2003/05/07 17:37:47 grumbel Exp $
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

#include "tank.hxx"
#include "mine.hxx"
#include "game_obj_manager.hxx"
#include "game_world.hxx"
#include "groundmap/ground_map.hxx"
#include "collision_manager.hxx"
#include "resource_manager.hxx"

Mine::Mine (boost::dummy_ptr<GameWorld>  w, const CL_Vector& arg_pos) 
  : GameObj (w),
    pos (arg_pos),
    hole (resources->get_sprite ("feuerkraft/hole")),
    active (2),
    detonated (false)
{
  GroundType type = get_world ()->get_groundmap ()->get_groundtype (pos.x, pos.y);
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
Mine::draw (View* view) 
{
  if (!is_active ())
    {
      view->draw (sur, pos);
    }
  else if (!detonated)
    {
      view->draw (sur_active, pos);
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
  GameObjManager* objs = get_world()->get_game_obj_manager();
  for (GameObjManager::iterator i = objs->begin(); i != objs->end(); ++i)
    {
      Vehicle* vehicle = dynamic_cast<Vehicle*>(*i);
      
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
