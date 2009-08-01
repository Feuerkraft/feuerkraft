//  $Id: sound_commands.cpp,v 1.2 2003/06/03 14:11:22 grumbel Exp $
//
//  Feuerkraft - A Tank Battle Game
//  Copyright (C) 2002 Ingo Ruhnke <grumbel@gmx.de>
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

#include "../sound/sound.hpp"
#include "sound_commands.hpp"

void
sound_play_music(const char* name)
{
}

void
sound_stop_music()
{
}

int
sound_play_sound(const char* name)
{
  PingusSound::play_sound(name);
  return 0; // Returning a handle is currently not supported 
}

void
sound_stop_sound(int handle)
{
}

/* EOF */
