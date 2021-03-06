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

#include <ClanLib/sound.h>
#include <iostream>
#include "../path_manager.hpp"
#include "../globals.hpp"

#include "sound_res_mgr.hpp"

SoundResMgr::SoundMap SoundResMgr::sound_map;

SoundHandle
SoundResMgr::load(const std::string& name)
{
  SoundMap::iterator i = sound_map.find(name);

  if (i == sound_map.end())
    {
      std::string filename = path_manager.complete("sounds/" + name + ".wav");
      CL_SoundBuffer* buffer = new CL_SoundBuffer(new CL_SoundProvider_Wave(filename, NULL), true);
      std::cout << "SoundResMgr: Loading sound from disk: "
                                 << name << " -> " << filename << std::endl;

      sound_map[name] = buffer;
      return buffer;
    }
  else
    {
      std::cout << "SoundResMgr: Loading sound from cache: " << name << std::endl;
      return i->second;
    }
}

/* EOF */
