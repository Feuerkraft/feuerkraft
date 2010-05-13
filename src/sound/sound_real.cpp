//  $Id: sound_real.cpp,v 1.2 2003/06/03 14:11:22 grumbel Exp $
//
//  Feuerkraft - A Tank Battle Game
//  Copyright (C) 2000 Ingo Ruhnke <grumbel@gmx.de>
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//  
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//  
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.


#include <ClanLib/sound.h>
#include <ClanLib/mikmod.h>
#include <ClanLib/Core/System/error.h>

#include <iostream>
#include "../globals.hpp"
#include "sound_res_mgr.hpp"
#include "sound_real.hpp"

#ifdef HAVE_LIBCLANVORBIS
#  include <ClanLib/vorbis.h>
#endif

#ifdef HAVE_LIBCLANMIKMOD
#  include <ClanLib/mikmod.h>
#  include <ClanLib/MikMod/setupmikmod.h>
#endif

namespace Sound {

PingusSoundReal::PingusSoundReal ()
  : output(), music_sample (0), music_session(0)
{
  std::cout << "Initializing ClanLib-Sound" << std::endl;

  CL_SetupSound::init();

  std::cout << "Initializing ClanLib-MikMod" << std::endl;

#ifdef HAVE_LIBCLANVORBIS
  CL_SetupVorbis::init();
#endif

#ifdef HAVE_LIBCLANMIKMOD
  CL_SetupMikMod::init();
#endif

  output = new CL_SoundOutput(44100);
}

PingusSoundReal::~PingusSoundReal()
{
  real_stop_music();

  delete output;

#ifdef HAVE_LIBCLANMIKMOD
  CL_SetupMikMod::deinit();
#endif

#ifdef HAVE_LIBCLANVORBIS
  CL_SetupVorbis::init();
#endif

  CL_SetupSound::deinit();
}

struct sound_is_finished
{
  bool operator()(CL_SoundBuffer_Session& sess) {
    return !sess.is_playing();
  }
};

void
PingusSoundReal::real_play_sound(const std::string& name, float volume, float panning)
{
  if (!sound_enabled)
    return;

  SoundHandle buffer;
  CL_SoundBuffer_Session sess;

  try {
    buffer = SoundResMgr::load(name);
    sess   = buffer->prepare();
  } catch (const CL_Error & e) {
    std::cout << "Can't open sound '" << name << "' -- skipping\n"
              << "  CL_Error: " << e.message << std::endl;
    return;
  }

  sess.set_volume(volume);
  sess.set_pan(panning);
  sess.set_looping(false);
  sess.play();
}

void
PingusSoundReal::real_stop_music ()
{
  if (music_session)
    {
      music_session->stop();
      delete music_session;
      music_session = 0;

      if (music_sample)
        {
          delete music_sample;
          music_sample = NULL;
        }
    }
}

void
PingusSoundReal::real_play_music (const std::string & arg_filename, float volume)
{
  std::string filename;

  filename = arg_filename;

  if (!music_enabled)
    return;

  std::cout << "PingusSoundReal: Playing music: " << filename << std::endl;

  real_stop_music();

  music_sample = 0;

  if (filename.substr(filename.size()-4, 4) == ".ogg")
    {
#ifdef HAVE_LIBCLANVORBIS
      music_sample = new CL_SoundBuffer (new CL_SoundProvider_Vorbis(filename.c_str()), true);
#else
      music_sample = 0;
#endif
    }
  else if (filename.substr(filename.size()-4, 4) == ".wav")
    {
      music_sample = new CL_SoundBuffer (new CL_SoundProvider_Wave(filename.c_str(), NULL), true);
    }
  else
    {  // MikMod should support the rest...
#ifdef HAVE_LIBCLANMIKMOD
      music_sample = new CL_SoundBuffer (new CL_SoundProvider_MikMod(filename.c_str()), true);
#else
      music_sample = 0;
#endif
    }

  if (music_sample)
    {
      music_session = new CL_SoundBuffer_Session(music_sample->prepare());
      music_session->set_volume(volume * 0.5f); // FIXME: music_volume
      music_session->set_looping(false);
      music_session->play();
    }
}

} // namespace Sound

/* EOF */

