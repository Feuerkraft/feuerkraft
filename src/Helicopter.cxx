//  $Id: Helicopter.cxx,v 1.3 2002/03/13 10:03:20 grumbel Exp $
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

#include "Projectile.hxx"
#include "Explosion.hxx"
#include "Helicopter.hxx"

extern CL_ResourceManager* resources;

Helicopter::Helicopter (boost::dummy_ptr<GameWorld>  w, CL_Vector arg_pos) 
  : Vehicle (w),
    rotor ("feuerkraft/rotor", resources),
    helidestroyed ("feuerkraft/helidestroyed", resources),
    rotor_count (0),
    velocity (0.0),
    angle (0.0),
    strafe (0.0),
    fireing (false),
    reloading (0),
    energie (100),
    destroyed (false)
{
  pos = arg_pos;
  storage.add (new SpriteProvider ("feuerkraft/helicopter", resources));
  storage.add (new SpriteProvider ("feuerkraft/helicopter_shadow", resources));
  heli = storage.create ("feuerkraft/helicopter");
  heli_shadow = storage.create ("feuerkraft/helicopter_shadow");
}

Helicopter::~Helicopter ()
{
}

void 
Helicopter::draw (View* view)
{
  if (!destroyed)
    {
      const float circle = 6.2831854f;
  
      heli_shadow->draw(int(view->get_x_offset () + pos.x + 25.0f),
			int(view->get_y_offset () + pos.y + 50.0f),
			angle/(circle/2.0)*180);

      heli->draw(int(view->get_x_offset () + pos.x),
		 int(view->get_y_offset () + pos.y),
		 angle/(circle/2.0)*180);
  /*
      view->draw (heli,
		  pos.x - heli.get_width ()/2,
		  pos.y - heli.get_height ()/2,
		  frame);*/

      view->draw (rotor,
		  int(pos.x - rotor.get_width ()/2),
		  int(pos.y - rotor.get_height ()/2),
		  (rotor_count = (rotor_count + 1) % 2));
      energie.draw (view, int(pos.x), int(pos.y - 40));
    }
  else
    {
      view->draw (helidestroyed,
		  int(pos.x - helidestroyed.get_width ()/2),
		  int(pos.y - helidestroyed.get_height ()/2));
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
  if (energie <= 0 && !destroyed)
    {
      world->add (new Explosion (world, pos, Explosion::MEDIUM));
      destroyed = true;
    }

  CL_Vector vel (-velocity, 0.0, 0.0);

  pos += vel.rotate (angle, CL_Vector (0.0, 0.0, 1.0)) * delta;
  pos += CL_Vector (0.0, strafe, 0.0).rotate (angle, CL_Vector (0.0, 0.0, 1.0)) * delta;

  velocity /= 1.03f;
  strafe /= 1.03f;

  if (fireing && !reloading)
    {
      float rot_angle = angle + 3.1415927;
      CL_Vector dir = CL_Vector (15.0, 0.0).rotate (rot_angle, CL_Vector (0.0, 0.0, 1.0));
      world->add (new Projectile (world, this, pos
				  + CL_Vector (0.0, -5.0, 0.0).rotate (rot_angle, CL_Vector (0.0, 0.0, 1.0)),
				  dir));
      reloading = 4;
    }

  //std::cout << "Fireing: " << fireing << " " << reloading << std::endl;

  if (reloading)
    --reloading;
}

void 
Helicopter::increase_velocity (float delta)
{
  velocity += 0.1f;
}

void 
Helicopter::decrease_velocity (float delta)
{
  velocity -= 0.1f;
}

void
Helicopter::turn_left (float )
{
  angle += 0.1f;
}

void 
Helicopter::turn_right (float )
{
  angle -= 0.1f;
}

void 
Helicopter::turn_left2 (float )
{
  strafe -= 0.1f;
}

void 
Helicopter::turn_right2 (float )
{
  strafe += 0.1f;
}

void
Helicopter::start_fire () 
{
  fireing = true;  
}

void 
Helicopter::stop_fire () 
{
  fireing = false;
}

bool 
Helicopter::is_colliding (CL_Vector obj_pos)
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
