//  $Id: helicopter.cxx,v 1.9 2003/06/05 21:17:11 grumbel Exp $
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

#include "projectile.hxx"
#include "explosion.hxx"
#include "helicopter.hxx"
#include "resource_manager.hxx"

Helicopter::Helicopter(FloatVector2d arg_pos) 
  : rotor (resources->get_sprite ("feuerkraft/rotor")),
    heli (resources->get_sprite ("feuerkraft/helicopter")),
    heli_shadow (resources->get_sprite ("feuerkraft/helicopter_shadow")),
    helidestroyed (resources->get_sprite ("feuerkraft/helidestroyed")),
    rotor_count (0),
    strafe (0.0),
    fireing (false),
    reloading (0),
    energie (100),
    destroyed (false)
{
  pos.x = arg_pos.x;
  pos.y = arg_pos.y;

  velocity = 0;
  orientation = 0;
}

Helicopter::~Helicopter ()
{
}

void 
Helicopter::draw (View& view)
{
  if (!destroyed)
    {
      view.draw (heli_shadow, FloatVector2d(pos.x + 25.0f, pos.y + 50.0f),
		  orientation);

      view.draw (heli, pos, orientation);
      /*
        view->draw (heli,
        pos.x - heli.get_width ()/2,
        pos.y - heli.get_height ()/2,
        frame);*/

      view.draw (rotor, pos);
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
  // Apply controlls
  orientation += 3.0f * steering * delta;
  velocity    += 15.0f * acceleration * delta;

  steering = acceleration = 0;

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

/* EOF */
