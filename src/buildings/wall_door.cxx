//  $Id: wall_door.cxx,v 1.10 2003/06/22 19:22:56 grumbel Exp $
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

#include "../vehicles/vehicle.hxx"
#include "../view.hxx"
#include "../game_obj_manager.hxx"
#include "../resource_manager.hxx"
#include "wall_door.hxx"

WallDoor::WallDoor(const AList& lst)
  : Building(lst)
{
  if (lst.get_string("orientation") == "vertical")
    {
      sprite = resources->get_sprite("feuerkraft/vdoor");
      pos = FloatVector2d(x_pos * 40 + 20, y_pos * 40 + 60);
      map_width = 1;
      map_height = 3;
    }
  else 
    {
      sprite = resources->get_sprite("feuerkraft/hdoor");
      pos = FloatVector2d(x_pos * 40 + 60, y_pos * 40 + 20);
      map_width = 3;
      map_height = 1;
    }
}

WallDoor::~WallDoor ()
{
}

void
WallDoor::draw (View& view)
{
  if (status != S_OPENED)
    view.draw(sprite, pos);
}

void
WallDoor::draw_radar (Radar& radar)
{
}

void
WallDoor::update(float)
{
  status = S_CLOSED;
  
  GameObjManager* objs = GameWorld::current()->get_game_obj_manager();

  for (GameObjManager::iterator i = objs->begin(); i != objs->end(); ++i)
    {
      Vehicle* vehicle = dynamic_cast<Vehicle*>(*i);
      if (vehicle)
	{
	  FloatVector2d diff = pos;
	  diff -= vehicle->get_pos ();

	  if (diff.get_length() < 75.0f)
	    {
	      status = S_OPENED;
	      return;
	    }
	}
    }
}

void
WallDoor::collide (Projectile*)
{
}

bool
WallDoor::is_active ()
{
  if (status == S_OPENED)
    return false;
  else
    return true;
}

bool
WallDoor::alive ()
{
  return true;
}

/* EOF */
