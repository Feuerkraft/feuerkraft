//  $Id: Tower.cxx,v 1.5 2002/03/17 16:42:25 grumbel Exp $
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

extern SpriteProviderStorage* storage;
extern CL_ResourceManager* resources;

#include "../Explosion.hxx"

Tower::Tower (boost::dummy_ptr<GameWorld> w, const TowerData& data)
  : Building (w),
    TowerData (data),
    towerbase (storage->get("feuerkraft/towerbase")),
    towerdamaged (storage->get("feuerkraft/towerdamaged")),
    towerdestroyed (storage->get("feuerkraft/towerdestroyed")),
    turret (storage->get("feuerkraft/towerturret")),
    energie (100),
    destroyed (false)
{  
  // FIXME: Hardcoded tilesize is ugly
  pos.x = x_pos * 40;
  pos.y = x_pos * 40;
}
  
// Draw the object onto the screen
void
Tower::draw (boost::dummy_ptr<View> view)
{
  //std::cout << "Tower::draw" << std::endl;

  if (energie > 50)
    {
      view->draw (&towerbase, pos);
    }
  else if (energie > 0)
    {
      view->draw (&towerdamaged, pos);
    }
  else
    {
      view->draw (&towerdestroyed, pos);
    }

  if (energie > 0)
    {
      view->draw (&turret, pos, angle);
      energie.draw (view, int(pos.x), int (pos.y) - 40);
    }
}
  
// Update the object once a game loop
void
Tower::update (float delta)
{
  if (!(energie > 0))
    return;

  angle += 1 * delta;

  if (angle >= 160)
    angle = 0;

  if (!destroyed && !(energie > 0))
    {
      get_world ()->add (new Explosion (get_world (), pos, Explosion::MEDIUM));
      destroyed = true;
    }
}


/* EOF */
