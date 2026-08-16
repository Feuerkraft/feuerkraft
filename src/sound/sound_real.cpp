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

#include <iostream>
#include "../globals.hpp"
#include "sound_real.hpp"

namespace Sound {

PingusSoundReal::PingusSoundReal()
  : music(nullptr)
{
  std::cout << "Initializing SDL2_mixer" << std::endl;
  if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) < 0)
    {
      std::cerr << "Mix_OpenAudio failed: " << Mix_GetError() << std::endl;
    }
  Mix_AllocateChannels(16);
}

PingusSoundReal::~PingusSoundReal()
{
  real_stop_music();
  Mix_CloseAudio();
}

void
PingusSoundReal::real_play_music(const std::string& filename, float volume)
{
  real_stop_music();
  music = Mix_LoadMUS(filename.c_str());
  if (!music)
    {
      std::cerr << "Failed to load music " << filename << ": " << Mix_GetError() << std::endl;
      return;
    }
  Mix_VolumeMusic(static_cast<int>(volume * MIX_MAX_VOLUME));
  Mix_PlayMusic(music, -1);
}

void
PingusSoundReal::real_stop_music()
{
  if (music)
    {
      Mix_HaltMusic();
      Mix_FreeMusic(music);
      music = nullptr;
    }
}

void
PingusSoundReal::real_play_sound(const std::string& filename, float volume, float panning)
{
  Mix_Chunk* chunk = Mix_LoadWAV(filename.c_str());
  if (!chunk)
    {
      std::cerr << "Failed to load sound " << filename << ": " << Mix_GetError() << std::endl;
      return;
    }
  int channel = Mix_PlayChannel(-1, chunk, 0);
  if (channel >= 0)
    {
      Mix_Volume(channel, static_cast<int>(volume * MIX_MAX_VOLUME));
      // panning: -1 left .. +1 right → 0..255
      Uint8 left  = static_cast<Uint8>((1.0f - panning) * 127.5f);
      Uint8 right = static_cast<Uint8>((1.0f + panning) * 127.5f);
      Mix_SetPanning(channel, left, right);
    }
  // Note: chunk is leaked per-play for simplicity during the port;
  // a proper SoundResMgr cache should own chunks long-term.
}

} // namespace Sound

/* EOF */
