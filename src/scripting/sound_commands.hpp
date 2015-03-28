//  $Id: sound_commands.hpp,v 1.3 2003/06/17 22:06:13 grumbel Exp $
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

#ifndef HEADER_SOUND_COMMANDS_HXX
#define HEADER_SOUND_COMMANDS_HXX

/** @addtogroup scripting */
//@{

void sound_play_music(const char* name);
void sound_stop_music();

int  sound_play_sound(const char* name);
void sound_stop_sound(int handle);

//@}

#endif

/* EOF */
