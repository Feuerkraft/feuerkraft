//  $Id: wall_door_data.hxx,v 1.1 2003/04/19 22:39:07 grumbel Exp $
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

#ifndef WALLDOORDATA_HXX
#define WALLDOORDATA_HXX

#include <guile/gh.h>
#include "BuildingData.hxx"

class WallDoorData : public BuildingData
{
protected:
  typedef enum { O_HORIZONTAL, O_VERTICAL } Orientation;
  float energie;
  int x_pos;
  int y_pos;
  Orientation orientation;

public:
  WallDoorData (SCM desc);
  virtual ~WallDoorData ();
  Building* create (boost::dummy_ptr<GameWorld> world);
  SCM dump_to_scm ();
};

#endif

/* EOF */
