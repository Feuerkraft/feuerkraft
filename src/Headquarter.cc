//  $Id: Headquarter.cc,v 1.4 2001/12/11 23:50:45 grumbel Exp $
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

#include "Flag.hh"
#include "Explosion.hh"
#include "Headquarter.hh"

extern CL_ResourceManager* resources;

Headquarter::Headquarter (boost::dummy_ptr<GameWorld> world, CL_Vector arg_pos)
  : Collideable (world),
    pos (arg_pos),
    headquarter ("feuerkraft/headquarter", resources),
    headquarter_damaged ("feuerkraft/headquarterdamaged", resources),
    headquarter_destroyed ("feuerkraft/headquarterdestroyed", resources),
    energie (100),
    destroyed (false)
{
  current_sur = &headquarter;
}

Headquarter::~Headquarter ()
{
}

void 
Headquarter::update (float delta)
{
  if (energie <= 0 && !destroyed)
    {
      world->add (new Explosion (world, pos, Explosion::MEDIUM));
      world->add (new Flag (world, pos));
      destroyed = true;
    }
}

void 
Headquarter::draw (View* view)
{
  view->draw (*current_sur, int(pos.x - current_sur->get_width ()/2), 
	      int(pos.y - current_sur->get_height ()/2));
  energie.draw (view, int(pos.x), int(pos.y - 40));
}

bool 
Headquarter::is_colliding (CL_Vector obj_pos)
{
  return (!destroyed &&
	  obj_pos.x > pos.x - 40 && obj_pos.x < pos.x + 40 &&
	  obj_pos.y > pos.y - 40 && obj_pos.y < pos.y + 40);
}

void 
Headquarter::collide (Projectile*)
{
  energie -= 10;

  if (energie > 60)
    current_sur = &headquarter;
  else if (energie > 0)
    current_sur = &headquarter_damaged;
  else
    current_sur = &headquarter_destroyed;
}

/* EOF */
