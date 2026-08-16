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
#include "sound_res_mgr.hpp"
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
  Mix_HaltChannel(-1);
  SoundResMgr::clear();
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
  // filename may be a short name or a complete path — try cache both ways
  Mix_Chunk* chunk = SoundResMgr::load_path(filename);
  if (!chunk)
    chunk = SoundResMgr::load(filename);
  if (!chunk)
    return;

  int channel = Mix_PlayChannel(-1, chunk, 0);
  if (channel >= 0)
    {
      Mix_Volume(channel, static_cast<int>(volume * MIX_MAX_VOLUME));
      float p = panning;
      if (p < -1.0f) p = -1.0f;
      if (p >  1.0f) p =  1.0f;
      Uint8 left  = static_cast<Uint8>((1.0f - p) * 127.5f);
      Uint8 right = static_cast<Uint8>((1.0f + p) * 127.5f);
      Mix_SetPanning(channel, left, right);
    }
}

} // namespace Sound

/* EOF */
