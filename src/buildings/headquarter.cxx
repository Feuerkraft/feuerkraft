//  $Id: headquarter.cxx,v 1.3 2003/05/10 22:41:28 grumbel Exp $
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

#include "../radar.hxx"
#include "../flag.hxx"
#include "../explosion.hxx"
#include "headquarter.hxx"
#include "resource_manager.hxx"

Headquarter::Headquarter (boost::dummy_ptr<GameWorld> world, const HeadquarterData& data)
  : Building (world, data.x_pos, data.y_pos),
    pos (x_pos * 40 + 40, y_pos * 40 + 40),
    headquarter (resources->get_sprite("feuerkraft/headquarter")),
    headquarter_damaged (resources->get_sprite("feuerkraft/headquarterdamaged")),
    headquarter_destroyed (resources->get_sprite("feuerkraft/headquarterdestroyed")),
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
      get_world()->add (new Explosion (get_world (), pos, Explosion::MEDIUM));
      get_world()->add (new Flag (get_world (), pos));
      destroyed = true;
    }
}

void 
Headquarter::draw (boost::dummy_ptr<View> view)
{
  view->draw (current_sur.get(), pos);
  energie.draw (view, int(pos.x), int(pos.y - 40));
}

void
Headquarter::draw_radar (boost::dummy_ptr<Radar> radar)
{
  radar->draw_blip (pos, 4);
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

bool
Headquarter::alive ()
{
  return (energie > 0);
}

/* EOF */
