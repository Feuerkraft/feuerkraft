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

#include <libguile.h>
#include "guile.hpp"
#include "game_obj_data_factory.hpp"

GameObjData*
GameObjDataFactory::create (SCM symbol, SCM data)
{
  /*
  if (Guile::equal_p(scm_from_utf8_symbol("tree"), symbol))
    {
      return new TreeData (data);
    }
  else*/
    if (Guile::equal_p(scm_from_utf8_symbol("tank"), symbol))
    {
      std::cout << "GameObjDataFactory::create: not implemented" << std::endl;
    }
  else
    {
      std::cout << "GameObjDataFactory: Unknown symbol: " << std::flush;
      scm_display(symbol, SCM_UNDEFINED);
      scm_newline(SCM_UNDEFINED);
    }
  return 0;
}

/* EOF */
