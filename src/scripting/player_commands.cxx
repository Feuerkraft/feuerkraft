//  $Id: player_commands.cxx,v 1.5 2003/06/04 13:10:09 grumbel Exp $
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
#include "../unit.hxx"
#include "../player.hxx"
#include "../game_obj_manager.hxx"
#include "player_commands.hxx"

extern Player* player;

void player_set_current_unit(int handle)
{
  GameObj* obj = GameObjManager::current()->get_object_by_id(handle);
  if (obj)
    {
      Unit* unit = dynamic_cast<Unit*>(obj);
      if (unit)
        player->set_current_unit(unit);
    }
  else
    {
      std::cout << __FUNCTION__ << ": No such object: " << handle << std::endl;
    }
}

int  player_get_current_unit()
{
  GameObj* game_obj = player->get_current_unit();
  return game_obj->get_id();
}

/* EOF */
