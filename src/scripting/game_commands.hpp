//  $Id: game_commands.hpp,v 1.2 2003/06/17 22:06:13 grumbel Exp $
//
//  Pingus - A free Lemmings clone
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

#ifndef HEADER_GAME_COMMANDS_HXX
#define HEADER_GAME_COMMANDS_HXX

/** @addtogroup scripting */
//@{

/** Pause the currently running game */
void game_pause();

/** Quit the currently running game */
void game_quit();

/** Load the game given by \a filename and replace the current one */
void game_load(const char* filename);

/** Dump the currently running game to filename (aka. creating a
    savegame) */
void game_save(const char* filename);

//@}

#endif

/* EOF */
