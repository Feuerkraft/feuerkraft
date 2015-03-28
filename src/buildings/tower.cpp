// Feuerkraft - A Tank Battle Game
// Copyright (C) 2000 Ingo Ruhnke <grumbel@gmx.de>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include <iostream>
#include "../property_set.hpp"
#include "../radar.hpp"
#include "../resource_manager.hpp"
#include "../input/controller.hpp"
#include "../math.hpp"
#include "../explosion.hpp"
#include "tower.hpp"

Tower::Tower(const AList& lst) :
  Building(lst),
  towerbase(resources->get_sprite("feuerkraft/tower/base")),
  towerdamaged (resources->get_sprite("feuerkraft/tower/damaged")),
  towerdestroyed (resources->get_sprite("feuerkraft/tower/destroyed")),
  turret (resources->get_sprite("feuerkraft/tower/turret")),
  steering(),
  orientation(),
  energie (lst.get_int("start-energie", 100)),
  destroyed (false),
  pos()
{
  //int energie;
  //std::cout << lst.retrieve_int("start-energie", energie) << std::endl;
  //std::cout << lst << std::endl;
  //std::cout << "Tower Energie: " << lst.get_int("start-energie", 100) << std::endl;
  //std::cout << "--Tower Energie: " << lst.get_int("sta-energie", 100) << std::endl;

  orientation = lst.get_float("orientation");
  pos.x = x_pos * 40 + 40;
  pos.y = y_pos * 40 + 40;

  steering = 0;

  Building::properties->register_float("orientation", &orientation);
}

Tower::~Tower ()
{
}

// Draw the object onto the screen
void
Tower::draw (View& view)
{
  if (energie > 50)
    {
      view.get_sc().color().draw(towerbase, pos.x, pos.y);
    }
  else if (energie > 0)
    {
      view.get_sc().color().draw(towerdamaged, pos.x, pos.y);
    }
  else
    {
      view.get_sc().color().draw(towerdestroyed, pos.x, pos.y);
    }

  if (energie > 0)
    {
      turret.set_angle(orientation);
      view.get_sc().color().draw(turret, pos.x, pos.y);
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
Tower::collide (int hits)
{
  energie -= hits;
  if (!destroyed && !(energie > 0))
    {
      GameWorld::current()->add (new Explosion (pos, Explosion::LARGE));
      destroyed = true;
    }
}

void
Tower::collide (Projectile*)
{
  energie -= 5;
  if (!destroyed && !(energie > 0))
    {
      GameWorld::current()->add (new Explosion (pos, Explosion::LARGE));
      destroyed = true;
    }
}

bool
Tower::alive ()
{
  return !destroyed;
}

/* EOF */
