//  $Id: sound.hpp,v 1.2 2003/06/03 14:11:22 grumbel Exp $
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

#ifndef HEADER_PINGUS_SOUND_HXX
#define HEADER_PINGUS_SOUND_HXX

#include <string>
#include "sounds.hpp"

class PingusSound
{
protected:
  /** FIXME: this should be SoundImpl, not PingusSound */
  static PingusSound* sound;

protected:
  PingusSound () { }
  virtual ~PingusSound () { }

  virtual void real_play_sound(const std::string & name, float volume, float panning) =0;
  virtual void real_play_music(const std::string & name, float volume) =0;
  virtual void real_stop_music() =0;

public:
  static void init (PingusSound* s = 0);
  static void deinit ();

  /** Load a sound file and play it immediately.

      @param name     Name of the sound, aka 'ohno'
      @param volume   volume
      @param panning  panning */
  static void play_sound(const std::string & name, float volume = 1.0f, float panning = 0.0f);

  static void play_music(const std::string & name, float volume = 1.0f);
  static void stop_music();

  static void play_sound(Sound::Name name, float volume = 1.0f, float panning = 0.0f);

private:
  PingusSound (const PingusSound&);
  PingusSound& operator= (const PingusSound&);
};

#endif

/* EOF */
