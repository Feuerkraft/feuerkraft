//  $Id: GameWorldData.hxx,v 1.3 2002/03/23 10:16:16 grumbel Exp $
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

#ifndef GAMEWORLDDATA_HXX
#define GAMEWORLDDATA_HXX

#include <guile/gh.h>
#include <list>

class GameObjData;
class GroundMapData;
class BuildingMapData;
class GameWorld;

class GameWorldData
{
protected:
  std::list<GameObjData*> gameobj_data;
  GroundMapData* groundmap_data;
  BuildingMapData* buildingmap_data;
  
public:
  GameWorldData ();
  GameWorldData (SCM desc);
  ~GameWorldData ();
  
  GameWorld* create ();
};

#endif

/* EOF */
