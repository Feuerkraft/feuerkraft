//  $Id: ammotent_data.hxx,v 1.3 2003/05/10 22:41:28 grumbel Exp $
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

#ifndef AMMOTENTDATA_HXX
#define AMMOTENTDATA_HXX

#include <guile/gh.h>
#include "building_data.hxx"

class AmmotentData : public BuildingData
{
public:
  float energie_value;

public:
  /** Format: (ammotent (pos 10 10) (energie 100)) */
  AmmotentData (SCM desc);

  SCM dump_to_scm ();

  Building* create (boost::dummy_ptr<GameWorld> world);
};

#endif

/* EOF */
