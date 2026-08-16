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

#include <iostream>
#include "../path_manager.hpp"
#include "sound_res_mgr.hpp"

SoundResMgr::SoundMap SoundResMgr::sound_map;

SoundHandle
SoundResMgr::load(const std::string& name)
{
  SoundMap::iterator i = sound_map.find(name);
  if (i != sound_map.end())
    return i->second;

  std::string path = path_manager.complete("sounds/" + name + ".wav");
  Mix_Chunk* chunk = Mix_LoadWAV(path.c_str());
  if (!chunk)
    {
      // try .ogg
      path = path_manager.complete("sounds/" + name + ".ogg");
      chunk = Mix_LoadWAV(path.c_str());
    }
  if (!chunk)
    {
      std::cerr << "SoundResMgr: failed to load " << name
                << ": " << Mix_GetError() << std::endl;
      return nullptr;
    }
  sound_map[name] = chunk;
  return chunk;
}

/* EOF */
