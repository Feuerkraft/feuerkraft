//  $Id: tower.cxx,v 1.9 2003/06/18 13:03:13 grumbel Exp $
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

#include "../property_set.hxx"
#include "../radar.hxx"
#include "../resource_manager.hxx"
#include "../input/controller.hxx"
#include "../math.hxx"
#include "../explosion.hxx"
#include "tower.hxx"

Tower::Tower(const TowerData& data)
  : Building(data.x_pos, data.y_pos),
    towerbase(resources->get_sprite("feuerkraft/towerbase")),
    towerdamaged (resources->get_sprite("feuerkraft/towerdamaged")),
    towerdestroyed (resources->get_sprite("feuerkraft/towerdestroyed")),
    turret (resources->get_sprite("feuerkraft/towerturret")),
    energie (int(data.start_energie)),
    destroyed (false)
{  
  orientation = data.orientation;
  pos.x = x_pos * 40 + 40;
  pos.y = y_pos * 40 + 40;

  steering = 0;

  properties->register_float("orientation", &orientation);
}
  
Tower::~Tower ()
{
}

// Draw the object onto the screen
void
Tower::draw (View& view)
{
  //std::cout << "Tower::draw" << std::endl;

  if (energie > 50)
    {
      view.draw (towerbase, pos);
    }
  else if (energie > 0)
    {
      view.draw (towerdamaged, pos);
    }
  else
    {
      view.draw (towerdestroyed, pos);
    }

  if (energie > 0)
    {
      view.draw (turret, pos, orientation);
    }
}
  
void
Tower::draw_energie (View& view)
{
  energie.draw (view, int(pos.x), int (pos.y) - 40);
}

void
Tower::draw_radar (Radar& radar)
{
  radar.draw_blip (pos, 4);
}

// Update the object once a game loop
void
Tower::update (float delta)
{
  if (!(energie > 0))
    return;

  orientation = Math::normalize_angle(orientation + steering * delta);

  if (!destroyed && !(energie > 0))
    {
      GameWorld::current()->add (new Explosion (pos, Explosion::MEDIUM));
      destroyed = true;
    }
}

void
Tower::update_controlls(const Controller& controller)
{
  steering = controller.get_axis_state(ORIENTATION_AXIS);
}

void 
Tower::collide (Projectile*)
{
  energie -= 5;   
  if (!destroyed && !(energie > 0))
    {
      GameWorld::current()->add (new Explosion (pos, Explosion::MEDIUM));
      destroyed = true;
    }
}

bool
Tower::alive ()
{
  return !destroyed;
}

/* EOF */
