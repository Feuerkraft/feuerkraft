//  $Id: AmmotentData.hxx,v 1.2 2002/03/17 22:32:08 grumbel Exp $
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
#include "BuildingData.hxx"

class AmmotentData : public BuildingData
{
public: // FIXME: Should be protected
  // FIXME: I know its redundant to have the position in every
  // FIXME: BuildingData thing, but I don't know a better way. (virtual
  // FIXME: inheritance might be one)
  int x_pos;
  int y_pos;
  float energie_value;

public:
  /** Format: (ammotent (pos 10 10))
   */
  AmmotentData (SCM desc);
  Building* create (boost::dummy_ptr<GameWorld> world);
};

#endif

/* EOF */
