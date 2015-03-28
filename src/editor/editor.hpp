// Feuerkraft - A Tank Battle Game
// Copyright (C) 2002 Ingo Ruhnke <grumbel@gmx.de>
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

#ifndef HEADER_FEUERKRAFT_EDITOR_HXX
#define HEADER_FEUERKRAFT_EDITOR_HXX

/** Editor Layer for Feuerkraft, its not a self standing editor, but
    more an in-game plug-in to manipulate the currently running world */
class Editor
{
private:
public:
  Editor();
private:
  Editor (const Editor&);
  Editor& operator= (const Editor&);
};

#endif

/* EOF */
