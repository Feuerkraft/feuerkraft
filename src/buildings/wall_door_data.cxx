//  $Id: wall_door_data.cxx,v 1.4 2003/06/03 14:11:22 grumbel Exp $
//
//  Feuerkraft - A Tank Battle Game
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
#include "wall_door.hxx"
#include "wall_door_data.hxx"

WallDoorData::WallDoorData (SCM desc)
{
  energie = 100;
  orientation = O_VERTICAL;

  // FIXME: No error handling
  while (gh_pair_p (desc))
    {
      SCM symbol = gh_caar(desc);
      SCM data   = gh_cdar(desc);

      if (gh_equal_p (gh_symbol2scm ("pos"), symbol))
	{
	  x_pos = gh_scm2int(gh_car (data));
	  y_pos = gh_scm2int(gh_cadr (data));
	}
      else if (gh_equal_p (gh_symbol2scm ("energie"), symbol))
	{
	  energie = gh_scm2double(gh_car (data));
	}
      else if (gh_equal_p (gh_symbol2scm ("orientation"), symbol))
	{
	  if (gh_equal_p (gh_symbol2scm ("horizontal"), gh_car(data)))
	    orientation = O_HORIZONTAL;
	  else
	    orientation = O_VERTICAL;
	}
      else
	{
	  std::cout << "WallDoorData: Error: " << std::flush;
	  gh_display(symbol);
	  std::cout << std::endl;
	}

      desc = gh_cdr (desc);
    }

}

WallDoorData::~WallDoorData ()
{
}

Building*
WallDoorData::create()
{
  return new WallDoor(*this);
}

SCM
WallDoorData::dump_to_scm ()
{
  return SCM_BOOL_F;
}

/* EOF */
