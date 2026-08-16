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

#ifndef HEADER_PINGUS_SOUND_RES_MGR_HXX
#define HEADER_PINGUS_SOUND_RES_MGR_HXX

#include <string>
#include <map>
#include <SDL_mixer.h>

typedef Mix_Chunk* SoundHandle;

/** Cache of Mix_Chunk* keyed by logical name or filesystem path. */
class SoundResMgr
{
private:
  typedef std::map<std::string, Mix_Chunk*> SoundMap;
  static SoundMap sound_map;

public:
  /** Load by short name under sounds/ (tries .wav then .ogg). */
  static SoundHandle load(const std::string& name);

  /** Load by absolute/complete path (used by play_sound with full paths). */
  static SoundHandle load_path(const std::string& path);

  /** Free all cached chunks (call on sound shutdown). */
  static void clear();

private:
  SoundResMgr(const SoundResMgr&);
  SoundResMgr& operator=(const SoundResMgr&);
};

#endif

/* EOF */
