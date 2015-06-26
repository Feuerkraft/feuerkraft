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

#ifndef HEADER_SCRIPT_HELPER_HXX
#define HEADER_SCRIPT_HELPER_HXX

#include <iostream>
#include "../ai_manager.hpp"
#include "../game_obj_manager.hpp"

namespace Scripting {

/** @return the object that has id */
template<class T>
T* get_object(int object_id)
{
  T* obj = dynamic_cast<T*>(GameObjManager::current()->get_object_by_id(object_id));

  if (obj)
    {
      return obj;
    }
  else
    {
      std::cout  << "Scripting: no object given by id: " << object_id << std::endl;
      return 0;
    }
}

inline
GameObj* get_object(int object_id)
{
  return GameObjManager::current()->get_object_by_id(object_id);
}

/** @return the AI for the given object or 0 if no AI is attached to
    the object */
template<class T>
T* get_ai(int object_id)
{
  GameObj* obj = GameObjManager::current()->get_object_by_id(object_id);

  if (obj)
    {
      AI* ai = AIManager::instance()->get_ai(obj);
      T* s_ai = 0;

      if (ai && (s_ai = dynamic_cast<T*>(ai)))
        return s_ai;
      else
        {
          std::cout << "Scripting: object doesn't have AI" << std::endl;
          return 0;
        }
    }
  else
    {
      std::cout  << "Scripting: no object given by id: " << object_id << std::endl;
      return 0;
    }
}

} // namespace Scripting

#endif

/* EOF */
