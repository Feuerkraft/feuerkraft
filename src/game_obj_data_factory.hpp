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

#ifndef GAMEOBJDATAFACTORY_HXX
#define GAMEOBJDATAFACTORY_HXX

#include <libguile.h>

class GameObjData;

class GameObjDataFactory
{
private:

public:
  /** Create a GameObjData out of a symbol and a data,
      FIXME: Abstractfactory stuff could be usefull here, but might
      FIXME: not be extremly important
      This function might return NULL on error! (no exceptions at the moment)
  */
  static GameObjData* create (SCM symbol, SCM data);
};

#endif

/* EOF */
