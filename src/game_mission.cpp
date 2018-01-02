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
#include <iostream>
#include "guile.hpp"
#include "game_mission.hpp"
#include "game_world.hpp"

GameMission::GameMission (SCM desc)
  : creation_time (0),
    world (0)
{
  if (SCM_NULLP(desc))
    {
      std::cout << "GameMission: SCM contains no data" << std::endl;
      // FIXME: Error handling
    }

  SCM symbol = SCM_CAAR(desc);

  if (Guile::equal_p(scm_from_utf8_symbol("feuerkraft-mission"), symbol))
    {
      std::cout << "GameMission: SCM is mission data" << std::endl;
    }
  else
    {
      std::cout << "GameMission: SCM is not mission-data" << std::endl;
      // FIXME: Error handling
    }

  desc = SCM_CDR(desc);

  while (!SCM_NULLP(desc))
    {
      // Current line
      SCM symbol = SCM_CAAR(desc);
      SCM data   = SCM_CDAR(desc);

      if (Guile::equal_p(scm_from_utf8_symbol("author-name"), symbol))
	{
	  author_name = Guile::scm2string(SCM_CADR(data));
	}
      else if (Guile::equal_p(scm_from_utf8_symbol("author-email"), symbol))
	{
	  author_email = Guile::scm2string(SCM_CADR(data));
	}
      else if (Guile::equal_p(scm_from_utf8_symbol("creation-time"), symbol))
	{
	  creation_time = scm_to_int(SCM_CADR(data));
	}
      else if (Guile::equal_p(scm_from_utf8_symbol("world"), symbol))
	{

	}

      // Goto next line
      desc = SCM_CDR(desc);
    }
}

GameMission::~GameMission ()
{
  delete world;
}


/* EOF */
