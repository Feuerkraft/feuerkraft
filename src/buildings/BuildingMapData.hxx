//  $Id: BuildingMapData.hxx,v 1.4 2002/03/23 12:20:43 grumbel Exp $
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

#ifndef BUILDINGMAPDATA_HXX
#define BUILDINGMAPDATA_HXX

#include <vector>
#include <guile/gh.h>
#include "../boost/dummy_ptr.hpp"

class BuildingData;
class BuildingMap;
class GameWorld;

/** The BuildingMap is something like a TileMap which holds pointers
    to all Buildings. It is used to hold the Building's instead of the
    GameWorld to make Collision Handling simpler and to guaranty that
    the buildings are correctly aligned.
*/
class BuildingMapData
{
protected:
  /** A list with all the buildings */
  std::vector<BuildingData*> buildings_data;

  int width;
  int height;
public:
  /** Format:
      (buildingmapdata (tower (angle 102)
                              (pos 10 20)))

      Where desc is only the cdr of the above thing.
   */
  BuildingMapData (SCM desc);
  
  BuildingMap* create (boost::dummy_ptr<GameWorld> world);
};

#endif

/* EOF */
