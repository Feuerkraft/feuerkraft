//  $Id: Projectile.cc,v 1.2 2001/02/18 13:53:34 grumbel Exp $
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

#include "Collideable.hh"
#include "Explosion.hh"
#include "Projectile.hh"

Projectile::Projectile (const CL_Vector& arg_pos, const CL_Vector& arg_add) :
  sur ("feuerkraft/projectile", resources),
  pos (arg_pos),
  tmp_pos (arg_pos),
  add (arg_add),
  lifetime (20 + rand () % 20 ),
  active (2)
{
  //std::cout << "Add: " << add.x << " " << add.y << std::endl;
}

Projectile::~Projectile ()
{
  
}

void 
Projectile::draw ()
{
  if (lifetime > 0) {
    sur.put_screen (pos.x - sur.get_width ()/2,
		    pos.y - sur.get_height ()/2);
  }

  //std::cout << "Pos: " << pos.x << " " << pos.y << std::endl;
  //CL_Display::draw_line (tmp_pos.x, tmp_pos.y, 
  //		 pos.x, pos.y, 1.0, 1.0, 1.0, 0.0);
}

void 
Projectile::update ()
{
  if (lifetime >= 0)
    {
      tmp_pos = pos;

      pos = pos + add;
      --lifetime;
    }

  if (lifetime < 0)
    detonate ();


  if (active > 0)
    {
      --active;
    }
  else
    {
      for (std::list<GameObj*>::iterator j = world->get_objects ().begin ();
	   j != world->get_objects ().end (); ++j)
	{
	  Collideable* collideable = dynamic_cast<Collideable*>(*j);
	  if (collideable)
	    {
	      if ((collideable)->is_colliding (get_pos ()))
		{
		  collideable->collide (this);
		  detonate ();
		}
	    }
	}
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
  world->add (new Explosion (pos));
}

/* EOF */
