//  $Id: TowerData.hxx,v 1.2 2002/03/17 00:16:50 grumbel Exp $
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

#ifndef TOWERDATA_HXX
#define TOWERDATA_HXX

#include <guile/gh.h>
#include "BuildingData.hxx"

class TowerData : public BuildingData
{
protected:
  // Angle in degree
  double angle;

public:
  /** Format:

  (tower (angle 23))

  Where 'desc' is only the cdr of the complete thing
  */
  TowerData (SCM desc);

  int map_width ()  { return 2; }
  int map_height () { return 2; }

  Building* create ();
};

#endif

/* EOF */
