//  $Id: player_commands.cxx,v 1.3 2003/06/03 14:11:22 grumbel Exp $
//
//  Feuerkraft - A Tank Battle Game
//  Copyright (C) 2002 Ingo Ruhnke <grumbel@gmx.de>
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

#include <iostream>
#include "../game_obj.hxx"
#include "../vehicle.hxx"
#include "../player.hxx"
#include "../controllable.hxx"
#include "../game_obj_manager.hxx"
#include "player_commands.hxx"

extern Player* player;

void player_set_current_vehicle(int handle)
{
  GameObj* obj = GameObjManager::current()->get_object_by_id(handle);
  if (obj)
    {
      Controllable* controllable = dynamic_cast<Controllable*>(obj);
      
      if (controllable)
        {
          Vehicle* vehicle = dynamic_cast<Vehicle*>(obj);
          if (vehicle != 0)
            player->set_current_vehicle(vehicle);
        }
      else
        {
          std::cout << __FUNCTION__ << ": Not a controllable: " << handle << std::endl;
        }
    }
  else
    {
      std::cout << __FUNCTION__ << ": No such object: " << handle << std::endl;
    }
}

int  player_get_current_vehicle()
{
  GameObj* game_obj = player->get_current_vehicle();
  return game_obj->get_id();
}

/* EOF */
