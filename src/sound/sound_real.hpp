// Feuerkraft - A Tank Battle Game
// Copyright (C) 2000 Ingo Ruhnke <grumbel@gmail.com>
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

#ifndef HEADER_PINGUS_SOUND_REAL_HXX
#define HEADER_PINGUS_SOUND_REAL_HXX

#include <string>
#include <SDL_mixer.h>
#include "sound.hpp"

namespace Sound {

/** SDL2_mixer-backed sound implementation. */
class PingusSoundReal : public PingusSound
{
private:
  Mix_Music* music;

public:
  PingusSoundReal();
  virtual ~PingusSoundReal();

  virtual void real_play_music(const std::string& filename, float volume);
  virtual void real_stop_music();
  virtual void real_play_sound(const std::string& filename, float volume, float panning);

private:
  PingusSoundReal(const PingusSoundReal&);
  PingusSoundReal& operator=(const PingusSoundReal&);
};

} // namespace Sound

#endif

/* EOF */
