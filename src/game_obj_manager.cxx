//  $Id: game_obj_manager.cxx,v 1.3 2003/06/03 14:11:22 grumbel Exp $
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

#include "game_obj.hxx"
#include "game_obj_manager.hxx"

GameObjManager* GameObjManager::current_manager = 0;

GameObjManager::GameObjManager(GameWorld* world)
  : game_world(world)
{
  current_manager = this;
  next_obj_id = 0;
}

int
GameObjManager::add_object(GameObj* obj)
{
  game_objs.push_back(obj);
  obj->set_id(next_obj_id);
  return next_obj_id++;
}

void
GameObjManager::remove_object(GameObj* obj)
{
  obj->remove();
}

GameObj*
GameObjManager::get_object_by_id(int id)
{
  for (GameObjs::iterator i = game_objs.begin(); i != game_objs.end(); ++i)
    {
      if ((*i)->get_id() == id)
        return *i;
    }
  return 0;
}

/* EOF */
