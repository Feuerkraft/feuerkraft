//  $Id: fuelstation_data.cxx,v 1.4 2003/06/03 14:11:22 grumbel Exp $
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
#include "../guile.hxx"
#include "fuelstation.hxx"
#include "fuelstation_data.hxx"

FuelstationData::FuelstationData (SCM desc)
{
  while (!gh_null_p (desc))
    {
      SCM symbol = gh_caar(desc);
      SCM data   = gh_cdar(desc);

      if (gh_equal_p (gh_symbol2scm ("pos"), symbol))
	{
	  x_pos = gh_scm2int(gh_car (data));
	  y_pos = gh_scm2int(gh_cadr (data));
	}
      else
	{
	  std::cout << "Fuelstation: Error: " << std::flush;
	  gh_display(symbol);
	  std::cout << std::endl;
	}

      desc = gh_cdr (desc);
    }
}

Building*
FuelstationData::create()
{
  return new Fuelstation(*this);
}

SCM
FuelstationData::dump_to_scm ()
{
  return SCM_BOOL_F; /*scm_listify (gh_symbol2scm ("fuelstation"), Guile::pos2scm (x_pos, y_pos),
                       SCM_UNDEFINED);*/
}

/* EOF */
