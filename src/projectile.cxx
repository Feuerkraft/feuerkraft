//  $Id: projectile.cxx,v 1.9 2003/05/18 21:15:06 grumbel Exp $
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

#include <iostream>
#include "property_set.hxx"
#include "collideable.hxx"
#include "view.hxx"
#include "collision_manager.hxx"
#include "explosion.hxx"
#include "buildings/building.hxx"
#include "buildings/building_map.hxx"
#include "game_obj_manager.hxx"
#include "projectile.hxx"
#include "resource_manager.hxx"

Projectile::Projectile (GameObjPtr p,
			const FloatVector2d& arg_pos, const FloatVector2d& arg_velocity)
  : sur (resources->get_sprite("feuerkraft/projectile")),
    tmp_pos (arg_pos),
    velocity (arg_velocity),
    lifetime (45 + rand () % 5 ),
    parent (p)
{
  //std::cout << "Velocity: " << velocity.x << " " << velocity.y << std::endl;
  pos  = arg_pos;
  
  properties->register_float("lifetime",   &lifetime);
  properties->register_float("x-pos",      &pos.x);
  properties->register_float("y-pos",      &pos.y);
  properties->register_float("velocity-x", &velocity.x);
  properties->register_float("velocity-y", &velocity.y);
}

Projectile::~Projectile ()
{
  
}

void 
Projectile::draw (ViewPtr view)
{
  if (lifetime > 0) {
    view->draw (sur, pos);
  }

  //std::cout << "Pos: " << pos.x << " " << pos.y << std::endl;
  //CL_Display::draw_line (tmp_pos.x, tmp_pos.y, 
  //		 pos.x, pos.y, 1.0, 1.0, 1.0, 0.0);
}

void 
Projectile::update (float delta)
{
  delta = delta * 50.0f;

  if (lifetime >= 0)
    {
      tmp_pos = pos;

      pos += velocity * delta;
      --lifetime; // FIXME: not delta clean
    }

  if (lifetime < 0)
    detonate ();

  CollisionManager::current()->add_point(get_id(), pos.x, pos.y);
}

bool 
Projectile::removable ()
{
  return (lifetime < 0);
}

void 
Projectile::detonate ()
{
  lifetime = -1;
  GameWorld::current()->add_front (new Explosion(pos));
}

void
Projectile::on_collision(GameObj* obj)
{
  if (Projectile::parent != obj)
    {
      std::cout << "Projectile " << get_id() << " touched gameobj " << obj->get_id() << std::endl;
      Collideable* collideable = dynamic_cast<Collideable*>(obj);
      if (collideable)
        {
          collideable->collide (this);
        }
      detonate();
    }
}

void
Projectile::on_collision_with_building(Building* building)
{
  std::cout << "Projectile touched building" << get_id() << std::endl;
  building->collide (this);      
  detonate ();
}

/* EOF */
