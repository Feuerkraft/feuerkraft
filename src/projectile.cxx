//  $Id: projectile.cxx,v 1.1 2003/04/19 22:39:07 grumbel Exp $
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

#include "boost/smart_ptr.hpp"
#include "Collideable.hxx"
#include "Explosion.hxx"
#include "buildings/Building.hxx"
#include "buildings/BuildingMap.hxx"
#include "Projectile.hxx"
#include "ResourceManager.hxx"

Projectile::Projectile (boost::dummy_ptr<GameWorld>  w, boost::dummy_ptr<GameObj> p,
			const CL_Vector& arg_pos, const CL_Vector& arg_velocity)
  : Collideable (w),
    sur (resources->get_sprite("feuerkraft/projectile")),
    tmp_pos (arg_pos),
    velocity (arg_velocity),
    lifetime (45 + rand () % 5 ),
    parent (p)
{
  //std::cout << "Velocity: " << velocity.x << " " << velocity.y << std::endl;
  pos  = arg_pos;
}

Projectile::~Projectile ()
{
  
}

void 
Projectile::draw (View* view)
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

  for (GameWorld::ObjIter j = world->get_objects ().begin ();
       j != world->get_objects ().end (); ++j)
    {
      if (*j != parent.get ())
	{ // Is this a lot slower than get_type() stuff?!
	  Collideable* collideable = dynamic_cast<Collideable*>(*j);
	  if (collideable)
	    {
	      if ((collideable)->is_colliding (get_pos ()))
		{
		  collideable->collide (this);
		  detonate ();
		  return;
		}
	    }
	}
    }

  Building* building = get_world ()->get_buildingmap ()->get_building (pos);
  if (building)
    {
      building->collide (this);      
      detonate ();
      return;
    }
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
  world->add_front (new Explosion (world, pos));
}

/* EOF */
