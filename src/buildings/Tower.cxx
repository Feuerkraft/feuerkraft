//  $Id: Tower.cxx,v 1.1 2002/03/16 23:41:07 grumbel Exp $
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

#include "Tower.hxx"

Tower::Tower (const TowerData& data)
  : TowerData (data),
    towerbase (storage->get("feuerkraft/towerbase")),
    towerdamaged (storage->get("feuerkraft/towerdamaged")),
    towerdestroyed (storage->get("feuerkraft/towerdestroyed")),
    turret (storage->get("feuerkraft/towerturret")),
    energie (100)
{  
}
  
// Draw the object onto the screen
void
Tower::draw (boost::dummy_ptr<View> view)
{
  if (energie > 50)
    {
      view->draw (&towerbase,
		  int(pos.x), int (pos.y));
    }
  else if (energie > 0)
    {
      view->draw (&towerdamaged, int(pos.x), int(pos.y));
    }
  else
    {
      view->draw (&towerdestroyed, int(pos.x), int(pos.y));
    }

  if (!destroyed)
    {
      view->draw (&turret, int(pos.x), int(pos.y));
      energie.draw (view, int(pos.x), int (pos.y) - 40);
    }
}
  
// Update the object once a game loop
void
Tower::update (float)
{
  delta = delta * 50.0f;

  if (destroyed)
    return;

  if (++angle >= 160)
    angle = 0;

  if (energie <= 0)
    {
      world->add (new Explosion (world, pos, Explosion::MEDIUM));
      destroyed = true;
    } 
}


/* EOF */
