//  $Id: helicopter.cpp,v 1.11 2003/06/22 17:22:47 grumbel Exp $
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

#include <iostream>
#include "../alist.hpp"
#include "../projectile.hpp"
#include "../explosion.hpp"
#include "../vehicle_ai.hpp"
#include "../ai_manager.hpp"
#include "../rocket.hpp"
#include "../resource_manager.hpp"
#include "../math.hpp"
#include "helicopter.hpp"

Helicopter::Helicopter(const AList& lst)
  : strafe (0.0),
    reloading (0),
    secondary_reload(0),
    energie (100),
    destroyed (false),
    ai(0)
{
  if (lst.get_int("type") == 0)
    {
      heli          = resources->get_sprite("feuerkraft/huey");
      heli_shadow   = resources->get_sprite("feuerkraft/huey_shadow");
      helidestroyed = resources->get_sprite("feuerkraft/helidestroyed");

      RotorDescription rotor;
      rotor.direction = RotorDescription::LEFT;
      rotor.slow_sprite ="feuerkraft/huey_rotor";
      rotor.fast_sprite = "feuerkraft/huey_rotor2";
      rotors.push_back(Rotor(rotor));
    }
  else if (lst.get_int("type") == 1)
    {
      heli          = resources->get_sprite("feuerkraft/helicopter");
      heli_shadow   = resources->get_sprite("feuerkraft/helicopter_shadow");
      helidestroyed = resources->get_sprite("feuerkraft/helidestroyed");

      RotorDescription rotor;
      rotor.direction = RotorDescription::LEFT;
      rotor.slow_sprite ="feuerkraft/huey_rotor";
      rotor.fast_sprite = "feuerkraft/huey_rotor2";
      rotors.push_back(Rotor(rotor));
    }
  else // if (lst.get_int("type") == 2)
    {
      heli          = resources->get_sprite("feuerkraft/chinook");
      heli_shadow   = resources->get_sprite("feuerkraft/chinook_shadow");
      helidestroyed = resources->get_sprite("feuerkraft/helidestroyed");

      RotorDescription rotor1;
      rotor1.offset = FloatVector2d(40.0f, 0);
      rotor1.slow_sprite = "feuerkraft/chinook_rotor";
      rotor1.fast_sprite = "feuerkraft/chinook_rotor2";
      rotor1.direction = RotorDescription::LEFT;
      rotors.push_back(Rotor(rotor1));

      RotorDescription rotor2;
      rotor2.offset = FloatVector2d(-40.0f, 0);
      rotor2.slow_sprite = "feuerkraft/chinook_rotor";
      rotor2.fast_sprite = "feuerkraft/chinook_rotor2";
      rotor2.direction = RotorDescription::RIGHT;
      rotors.push_back(Rotor(rotor2));
    }

  pos.x = lst.get_float("x-pos");
  pos.y = lst.get_float("y-pos");

  velocity = 0;
  orientation = 0;

  height = 0;
  state = LANDED;
}

Helicopter::~Helicopter ()
{
}

void
Helicopter::draw (View& view)
{
  if (!destroyed)
    {
      heli_shadow.set_angle(Math::rad2deg(orientation));
      view.get_sc().color().draw(heli_shadow, pos.x + height/2.0f, pos.y + height);

      heli.set_angle(Math::rad2deg(orientation));
      view.get_sc().color().draw(heli, pos.x, pos.y);

      for (Rotors::iterator i = rotors.begin(); i != rotors.end(); ++i)
        {
          (*i).draw(view, pos, orientation);
        }

      energie.draw(view, int(pos.x), int(pos.y - 40));
    }
  else
    {
      helidestroyed.set_angle(Math::rad2deg(orientation));
      view.get_sc().color().draw(helidestroyed, pos.x, pos.y);
    }
}

void
Helicopter::update (float delta)
{
  for (Rotors::iterator i = rotors.begin(); i != rotors.end(); ++i)
    (*i).update(delta);

  if (state == LANDING)
    {
      height -= 20.0f * delta;
      if (height < 0.0f)
        {
          height = 0;
          state = LANDED;

          for (Rotors::iterator i = rotors.begin(); i != rotors.end(); ++i)
            (*i).stop();
        }
    }
  else if (state == STARTING)
    {
      bool running = true;
      for (Rotors::iterator i = rotors.begin(); i != rotors.end(); ++i)
        if (!(*i).is_running())
          running = false;

      if (running)
        {
          height += 20.0f * delta;
          if (height > 50.0f)
            {
              height = 50;
              state = FLYING;
            }
        }
    }

  // Apply controlls
  if (state != LANDED && height > 0)
    {
      orientation += 3.0f  * steering * delta;
      velocity    -= 15.0f * acceleration * delta;
      strafe      -= 5.0f  * strafe_steering * delta;
    }

  strafe_steering = steering = acceleration = 0;

  if (secondary_firing && secondary_reload > .1)
    {
      secondary_reload = 0;
      GameWorld::current()->add (new Projectile (this, get_pos(),
                                                 FloatVector2d::make_polar(20 + Math::frand()*2.0f,
                                                                           orientation + 3.1415927f
                                                                           + Math::frand()*0.06f - 0.03f)));
    }
  secondary_reload += delta;

  delta *= 50;

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

  if (firing && !reloading)
    {
      GameWorld::current()->add(new Rocket(get_pos(), orientation + 3.1415927f));
      reloading = 10;
    }

  if (reloading)
    --reloading;
}

void
Helicopter::land_or_start()
{
  if (state == FLYING || state == STARTING)
    {
      state = LANDING;
    }
  else if (state == LANDED || state == LANDING)
    {
      state = STARTING;
      for (Rotors::iterator i = rotors.begin(); i != rotors.end(); ++i)
        (*i).start();
    }
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
