//  $Id: tower_data.hxx,v 1.5 2003/06/03 14:11:22 grumbel Exp $
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

#ifndef TOWERDATA_HXX
#define TOWERDATA_HXX

#include <guile/gh.h>
#include "building_data.hxx"

class TowerData : public BuildingData
{
public:
  // Angle in degree
  double angle;
  double start_energie;

  /** Format:

  (tower (angle 23))

  Where 'desc' is only the cdr of the complete thing
  */
  TowerData (SCM desc);

  SCM dump_to_scm ();

  Building* create();
};

#endif

/* EOF */
