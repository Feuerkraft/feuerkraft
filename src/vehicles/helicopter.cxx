//  $Id: helicopter.cxx,v 1.11 2003/06/22 17:22:47 grumbel Exp $
//
//  Feuerkraft - A Tank Battle Game
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

#include <iostream>
#include "../alist.hxx"
#include "../projectile.hxx"
#include "../explosion.hxx"
#include "../vehicle_ai.hxx"
#include "../ai_manager.hxx"
#include "../resource_manager.hxx"
#include "helicopter.hxx"

Helicopter::Helicopter(const AList& lst)
  : rotor (resources->get_sprite ("feuerkraft/huey_rotor")),
    heli (resources->get_sprite ("feuerkraft/huey")),
    heli_shadow (resources->get_sprite ("feuerkraft/huey_shadow")),
    helidestroyed (resources->get_sprite ("feuerkraft/helidestroyed")),
    rotor_count (0),
    strafe (0.0),
    fireing (false),
    reloading (0),
    energie (100),
    destroyed (false),
    ai(0)
{
  pos.x = lst.get_float("x-pos");
  pos.y = lst.get_float("y-pos");

  velocity = 0;
  orientation = 0;

  height = 50.0f;

  state = FLYING;
}

Helicopter::~Helicopter ()
{
}

void 
Helicopter::draw (View& view)
{
  if (!destroyed)
    {
      view.draw (heli_shadow, FloatVector2d(pos.x + height/2.0f, pos.y + height),
                 orientation);

      view.draw (heli, pos, orientation);
      /*
        view->draw (heli,
        pos.x - heli.get_width ()/2,
        pos.y - heli.get_height ()/2,
        frame);*/

      view.draw (rotor, pos, rotor_count);
      energie.draw (view, int(pos.x), int(pos.y - 40));
    }
  else
    {
      view.draw (helidestroyed, pos, orientation);
    }

  /*
    view->draw_rect (int(pos.x) - 40, int(pos.y) - 10, 
    int(pos.x) + 30, int(pos.y) + 10, 
    1.0f, 1.0f, 1.0f);
    view->draw_rect (int(pos.x) - 15, int(pos.y) - 20, 
    int(pos.x) + 5, int(pos.y) + 20, 
    1.0f, 1.0f, 1.0f);*/
}

void 
Helicopter::update (float delta)
{
  if (state == LANDING)
    {
      height -= 20.0f * delta;
      if (height < 0.0f)
        {
          height = 0;
          state = LANDED;
        }
    }
  else if (state == STARTING)
    {
      height += 20.0f * delta;
      if (height > 50.0f)
        {
          height = 50;
          state = FLYING;
        }
    }
    
  // Apply controlls
  if (state != LANDED)
    {
      orientation += 3.0f * steering * delta;
      velocity    -= 15.0f * acceleration * delta;
      strafe      -= 3.0f * strafe_steering * delta;
    }

  strafe_steering = steering = acceleration = 0;

  rotor_count -= 10 * delta;
  delta *= 50;
  rotor.update (delta);

  if (energie <= 0 && !destroyed)
    {
      GameWorld::current()->add(new Explosion (pos, Explosion::MEDIUM));
      destroyed = true;
    }

  FloatVector2d vel(velocity, 0.0);
 
  pos += vel.rotate(orientation);

  // Let the heli strafe
  pos += FloatVector2d(0.0, strafe).rotate(orientation) * delta;

  velocity /= 1.03f;
  strafe   /= 1.03f;

  if (fireing && !reloading)
    {
      float rot_orientation = orientation;
      FloatVector2d dir = FloatVector2d (15.0, 0.0).rotate(rot_orientation);
      GameWorld::current()->add (new Projectile(this, pos
                                                + FloatVector2d (0.0, -5.0).rotate (rot_orientation),
                                                dir));
      reloading = 4;
    }

  //std::cout << "Fireing: " << fireing << " " << reloading << std::endl;

  if (reloading)
    --reloading;
}

void
Helicopter::land_or_start()
{
  if (state == FLYING || state == STARTING)
    state = LANDING;
  else if (state == LANDED || state == LANDING)
    state = STARTING;
}

bool 
Helicopter::is_colliding (FloatVector2d obj_pos)
{
  float range = 20.0; 

  return  (obj_pos.x > pos.x - range && obj_pos.x < pos.x + range
	   && obj_pos.y > pos.y - range && obj_pos.y < pos.y + range);
}

void
Helicopter::collide (Projectile*) 
{
  energie -= 15;
}

void
Helicopter::attach_ai()
{
  ai = new VehicleRoboAI(this);
  AIManager::instance()->add(ai);
}

void
Helicopter::dettach_ai()
{
  if (ai)
    {
      AIManager::instance()->remove(ai);
      delete ai;
      ai = 0;
    }

}

/* EOF */