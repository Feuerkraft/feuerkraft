//  $Id: TowerData.cxx,v 1.2 2002/03/17 00:16:50 grumbel Exp $
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
#include "Tower.hxx"
#include "TowerData.hxx"

TowerData::TowerData (SCM desc)
{
  while (!gh_null_p (desc))
    {
      SCM symbol = gh_caar(desc);
      SCM data   = gh_cdar(desc);

      if (gh_equal_p (gh_symbol2scm ("angle"), symbol))
	{
	  angle = gh_scm2double(gh_car (data));
	}
      else
	{
	  std::cout << "TowerData: Error: " << std::flush;
	  std::cout << symbol << std::endl;
	}
    }
}

Building* 
TowerData::create ()
{
  return new Tower (0, *this); // FIXME: Bug!
}

/* EOF */
