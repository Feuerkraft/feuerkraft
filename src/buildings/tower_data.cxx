//  $Id: tower_data.cxx,v 1.5 2003/06/18 13:03:13 grumbel Exp $
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
#include "../ai_manager.hxx"
#include "tower.hxx"
#include "tower_ai.hxx"
#include "tower_data.hxx"

TowerData::TowerData (SCM desc)
{
  // Default values
  start_energie = 100.0f;
  orientation = 0;

  while (!gh_null_p (desc))
    {
      SCM symbol = gh_caar(desc);
      SCM data   = gh_cdar(desc);

      if (gh_equal_p (gh_symbol2scm ("angle"), symbol))
	{
	  orientation = gh_scm2double(gh_car (data));
	}
      else if (gh_equal_p (gh_symbol2scm ("pos"), symbol))
	{
	  x_pos = gh_scm2int(gh_car (data));
	  y_pos = gh_scm2int(gh_cadr (data));
	}
      else if (gh_equal_p (gh_symbol2scm ("energie"), symbol))
	{
	  start_energie = gh_scm2double (gh_car (data));
	}
      else
	{
	  std::cout << "TowerData: Error: " << std::flush;
	  gh_display(symbol);
	  std::cout << std::endl;
	}

      desc = gh_cdr (desc);
    }
}

Building* 
TowerData::create()
{
  // FIXME: not really the right place for this
  Tower* tower = new Tower(*this);
  AIManager::instance()->add(new TowerAI(tower));
  return tower;
}

SCM
TowerData::dump_to_scm ()
{
  return SCM_BOOL_F;
}

/* EOF */
