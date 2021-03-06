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

#ifndef HEADER_AI_COMMANDS_HXX
#define HEADER_AI_COMMANDS_HXX

void ai_goto(int handle, float x, float y);
void ai_stop(int handle);

/** Check if an object has an AI attached to it
    @return true if object has AI, false otherwise */
bool ai_has(int handle);

/** Attach an AI object to an GameObject if it doesn't already have an
    AI */
void ai_attach(int handle);

void ai_dettach(int handle);

#endif

/* EOF */
