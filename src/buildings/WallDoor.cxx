//  $Id: WallDoor.cxx,v 1.3 2002/04/02 09:52:57 grumbel Exp $
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

#include "../Vehicle.hxx"
#include "../View.hxx"
#include "WallDoor.hxx"
#include "ResourceManager.hxx"

WallDoor::WallDoor (boost::dummy_ptr<GameWorld> world, const WallDoorData& data)
  : Building (world),
    WallDoorData (data)
{
  switch (orientation)
    {
    case O_VERTICAL:
      sprite = resources->get_sprite("feuerkraft/vdoor");
      pos = CL_Vector (x_pos * 40 + 20, y_pos * 40 + 60);
      map_width = 1;
      map_height = 3;
      break;
    case O_HORIZONTAL:
    default:
      sprite = resources->get_sprite("feuerkraft/hdoor");
      pos = CL_Vector (x_pos * 40 + 60, y_pos * 40 + 20);
      map_width = 3;
      map_height = 1;
      break;
    }
}

WallDoor::~WallDoor ()
{
}

void
WallDoor::draw (boost::dummy_ptr<View> view)
{
  if (status != S_OPENED)
    view->draw (sprite, pos);
}

void
WallDoor::draw_radar (boost::dummy_ptr<Radar> radar)
{
}

void
WallDoor::update(float)
{
  status = S_CLOSED;

  for (GameWorld::ObjIter j = get_world ()->get_objects ().begin ();
       j != get_world ()->get_objects ().end (); ++j)
    {
      Vehicle* vehicle = dynamic_cast<Vehicle*>(*j);
      if (vehicle)
	{
	  CL_Vector diff = pos;
	  diff -= vehicle->get_pos ();

	  if (diff.norm () < 75.0f)
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
