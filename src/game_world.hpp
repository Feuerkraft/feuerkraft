//  $Id: game_world.hpp,v 1.13 2003/06/22 21:51:21 grumbel Exp $
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

#ifndef GAMEWORLD_HH
#define GAMEWORLD_HH

#include "vector2d.hpp"
#include "game_world_data.hpp"

class View;
class LevelMap;
class GameObj;
class GroundMap;
class BuildingMap;
class TriggerManager;
class GameObjManager;
class BuildingManager;
class GameWorld;

typedef GameWorld* GameWorldPtr;

class GameWorld : public GameWorldData
{
private:
  friend class GameWorldBuilder;

  GameObjManager*  game_obj_manager;
  BuildingManager* building_manager;
  TriggerManager*  trigger_manager;

  // FIXME: This is a ugly ugly hack...
  GameObj* buildingmap;
  
  GroundMap* groundmap;
  float current_time;
  FloatVector2d wind;
  SCM world_module;
  SCM last_module;

public:
  GameWorld (SCM scm);
  ~GameWorld ();

  float get_time() { return current_time; }
  
  /** @return the current speed and direction of the wind */
  FloatVector2d get_wind() const;

  /// Return a reference to the objects in the world
  void add(GameObj*);
  void add_front(GameObj*);

  void draw(View& view);
  void draw_energie(View& view);
  void draw_levelmap(LevelMap& levelmap);
  void update(float delta);

  BuildingMap* get_buildingmap ();
  GroundMap*   get_groundmap ();
  GameObjManager* get_game_obj_manager();

private:
  static GameWorld* current_world;
public:
  static GameWorld* current() { return current_world; }
};

#endif

/* EOF */
