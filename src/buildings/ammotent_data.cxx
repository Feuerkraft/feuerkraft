//  $Id: ammotent_data.cxx,v 1.4 2003/06/03 14:11:22 grumbel Exp $
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
#include "ammotent.hxx"
#include "ammotent_data.hxx"

AmmotentData::AmmotentData (SCM desc)
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
      else if (gh_equal_p (gh_symbol2scm ("energie"), symbol))
	{
	  energie_value = gh_scm2double(gh_car (data));
	}
      else
	{
	  std::cout << "Ammotent: Error: " << std::flush;
	  gh_display(symbol);
	  std::cout << std::endl;
	}

      desc = gh_cdr (desc);
    }
}

Building* 
AmmotentData::create ()
{
  return new Ammotent (*this);
}

SCM
AmmotentData::dump_to_scm ()
{
  SCM ret = SCM_EOL;
  
  ret = gh_cons(gh_symbol2scm ("ammotent"),
		gh_cons(Guile::pos2scm (x_pos, y_pos), ret));

			//gh_cons(gh_list (gh_symbol2scm ("energie"), gh_double2scm (energie_value)),
			///ret)));
  return ret;
}

/* EOF */
