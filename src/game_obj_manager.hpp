//  $Id: game_obj_manager.hpp,v 1.4 2003/06/03 14:11:22 grumbel Exp $
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

#ifndef HEADER_GAME_OBJ_MANAGER_HXX
#define HEADER_GAME_OBJ_MANAGER_HXX

#include <list>

class GameObj;
class GameWorld;

/** */
class GameObjManager
{
public:
  typedef std::list<GameObj*> GameObjs;
  typedef GameObjs::iterator    iterator;
  
private:
  int next_obj_id;
  GameObjs   game_objs;
  GameWorld* game_world;

  static GameObjManager* current_manager;
public:

  static GameObjManager* current() { return current_manager; }

  GameObjManager(GameWorld* world);
  /**  */
  GameObj* get_object_by_id(int id);

  /**  */
  int add_object(GameObj* obj);

  void remove_object(GameObj* obj);

  GameObjs& get_objects() { return game_objs; }

  iterator begin() { return game_objs.begin(); }
  iterator end()   { return game_objs.end(); }

  GameWorld* get_world() { return game_world; }

  template<class Func>
  void for_each_game_obj(Func func) {
    for (GameObjs::iterator i = game_objs.begin(); i != game_objs.end(); ++i)
      {
        func(**i);
      }
  }
private:
  GameObjManager (const GameObjManager&);
  GameObjManager& operator= (const GameObjManager&);
};

#endif

/* EOF */
