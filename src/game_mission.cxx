//  $Id: game_mission.cxx,v 1.3 2003/05/02 14:28:26 grumbel Exp $
//
//  Pingus - A free Lemmings clone
//  Copyright (C) 2000 Ingo Ruhnke <grumbel@gmx.de>
//
//  This program is free software; you can redistribute it and/or
//  modify it under the terms of the GNU General Public License
//  as published by the Free Software Foundation; either version 2
//  of the License, or (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program; if not, write to the Free Software
//  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

#include <guile/gh.h>
#include <iostream>
#include "guile.hxx"
#include "game_mission.hxx"
#include "game_world.hxx"

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
 
  if (Guile::equal_p(scm_str2symbol("feuerkraft-mission"), symbol))
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

      if (Guile::equal_p(scm_str2symbol("author-name"), symbol))
	{
	  author_name = Guile::scm2string(SCM_CADR(data));
	}
      else if (Guile::equal_p(scm_str2symbol("author-email"), symbol))
	{
	  author_email = Guile::scm2string(SCM_CADR(data));
	}
      else if (Guile::equal_p(scm_str2symbol("creation-time"), symbol))
	{
	  creation_time = gh_scm2int(SCM_CADR(data));
	}
      else if (Guile::equal_p(scm_str2symbol("world"), symbol))
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
