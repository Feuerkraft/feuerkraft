// Feuerkraft - A Tank Battle Game
// Copyright (C) 2002 Ingo Ruhnke <grumbel@gmail.com>
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

#include "assert.hpp"
#include "game_obj.hpp"
#include "game_obj_manager.hpp"

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
  AssertMsg(obj, "GameObjManager: No valid GameObj passed!");

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
