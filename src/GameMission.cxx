//  $Id: GameMission.cxx,v 1.1 2002/03/10 19:56:00 grumbel Exp $
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

#include <iostream>
#include "GameMission.hxx"

GameMission::GameMission (SCM desc)
  : creation_time (0),
    world (0)    
{
  if (gh_null_p (desc))
    {
      std::cout << "GameMission: SCM contains no data" << std::endl;
      // FIXME: Error handling
    }

  SCM symbol = gh_caar(desc);
 
  if (gh_equal_p (gh_symbol2scm ("feuerkraft-mission"), symbol))
    {
      std::cout << "GameMission: SCM is mission data" << std::endl;
    }
  else
    {
      std::cout << "GameMission: SCM is not mission-data" << std::endl;
      // FIXME: Error handling
    }
  
  desc = gh_cdr (desc);

  while (!gh_null_p (desc))
    {
      // Current line
      SCM symbol = gh_caar(desc);
      SCM data   = gh_cdar(desc);

      if (gh_equal_p (gh_symbol2scm ("author-name"), symbol))
	{
	  char* str = gh_scm2newstr(gh_cadr (data), 0);
	  author_name = str;
	  free (str);
	}
      else if (gh_equal_p (gh_symbol2scm ("author-email"), symbol))
	{
	  char* str = gh_scm2newstr(gh_cadr (data), 0);
	  author_email = str;
	  free (str);
	}
      else if (gh_equal_p (gh_symbol2scm ("creation-time"), symbol))
	{
	  creation_time = gh_scm2int (gh_cadr (data));
	}
      else if (gh_equal_p (gh_symbol2scm ("world"), symbol))
	{
	  
	}
      
      // Goto next line
      desc = gh_cdr (desc);
    }
}

GameMission::~GameMission ()
{
  delete world;
}


/* EOF */
