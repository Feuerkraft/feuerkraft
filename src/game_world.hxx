//  $Id: game_world.hxx,v 1.3 2003/05/01 20:56:39 grumbel Exp $
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

#ifndef GAMEWORLD_HH
#define GAMEWORLD_HH

#include <list>
#include "boost/smart_ptr.hpp"
#include "game_obj.hxx"
#include "game_obj_manager.hxx"
#include "game_world_data.hxx"
#include "view.hxx"

class View;
class LevelMap;
class GameObj;
class GroundMap;
class BuildingMap;

class GameWorld : public GameWorldData
{
private:
  GameObjManager game_obj_manager;

  // FIXME: This is a ugly ugly hack...
  GameObj* buildingmap;
  
  GroundMap* groundmap;
  float current_time;

public:
  typedef GameObjManager::iterator ObjIter;

  GameWorld ();
  GameWorld (const GameWorldData& data);
  ~GameWorld ();

  /** Sync the GameWorld with its GameWorldData parent, in the ideal case
      this shouldn't be necessary, but sometimes it is required. */
  GameWorldData* get_data ();
  
  float get_time() { return current_time; }

  GameObjManager::GameObjs& get_objects() { return game_obj_manager.get_objects(); }

  /// Return a reference to the objects in the world
  void add (GameObj*);
  void add_front (GameObj*);

  void draw (View* view);
  void draw_energie (View* view);
  void draw_levelmap (LevelMap* levelmap);
  void update (float delta);

  BuildingMap* get_buildingmap ();
  GroundMap*   get_groundmap ();
};

#endif

/* EOF */
