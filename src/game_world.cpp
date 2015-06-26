// Feuerkraft - A Tank Battle Game
// Copyright (C) 2000 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include <iostream>
#include <algorithm>
#include <functional>

#include "mine.hpp"
#include "vehicles/tank.hpp"
#include "projectile.hpp"
#include "game_world.hpp"
#include "groundmap/ground_map_data.hpp"
#include "groundmap/ground_map.hpp"
#include "game_obj.hpp"
#include "math.hpp"
#include "game_obj_data.hpp"
#include "game_obj_manager.hpp"
#include "view.hpp"
#include "path_manager.hpp"
#include "trigger_manager.hpp"
#include "buildings/building_manager.hpp"
#include "buildings/building_map.hpp"

GameWorld* GameWorld::current_world = 0;

GameWorld::GameWorld (SCM scm)
  : GameWorldData (scm),
    game_obj_manager(new GameObjManager(this)),
    building_manager(new BuildingManager()),
    trigger_manager (new TriggerManager()),
    current_time(0.0f),
    wind(40.0f, 30.0f)
{
  current_world = this;

  if (groundmap_data)
    groundmap = groundmap_data->create ();//this);

  if (buildingmap_data)
    buildingmap = buildingmap_data->create();

  if (!groundmap)
    {
      std::cout << "GameWorld: No groundmap created, bailout" << std::endl;
      assert(groundmap);
    }

  if (!buildingmap)
    {
      std::cout << "GameWorld: No buildingmap created, bailout" << std::endl;
      assert(buildingmap);
    }

  game_obj_manager->add_object(groundmap);
  game_obj_manager->add_object(buildingmap);

  for (std::vector<GameObjData*>::iterator i = gameobj_data.begin (); i != gameobj_data.end (); ++i)
    {
      game_obj_manager->add_object((*i)->create());
    }

  // FIXME: a little hacky
  //world_module = scm_c_define_module("feuerkraft game-world", 0, 0);
  //last_module  = scm_set_current_module(world_module);

  // Load scripts
  for(std::vector<std::string>::iterator i = scripts.begin(); i != scripts.end(); ++i)
    {
      std::cout << "### Loading Script: " << *i << std::endl;
      scm_c_primitive_load((path_manager.complete("missions/" + *i)).c_str());
      std::cout << "### DONE: Loading Script: " << *i << std::endl;
    }
}

GameWorld::~GameWorld ()
{
  delete game_obj_manager;
  delete building_manager;
  delete trigger_manager;
  // FIXME: Memory Leak, we should clear the gameobj list here

  // Restore module FIXME: a little hacky
  //scm_set_current_module(last_module);
}

void
GameWorld::add (GameObj* obj)
{
  game_obj_manager->add_object(obj);
}

void
GameWorld::add_front (GameObj* obj)
{
  // FIXME: no go...
  game_obj_manager->add_object(obj);
}

struct z_pos_sorter
{
  bool operator() (GameObj* a, GameObj* b)
  {
    return a->get_z_pos () < b->get_z_pos ();
  }
};

void
GameWorld::draw (View& view)
{
  game_obj_manager->get_objects().sort (z_pos_sorter ());

  GameObjManager* objs = game_obj_manager;
  for (GameObjManager::iterator i = objs->begin(); i != objs->end(); ++i)
    {
      if (!(*i)->is_hidden())
        (*i)->draw (view);
    }
}

void
GameWorld::draw_energie (View& view)
{
  GameObjManager* objs = game_obj_manager;
  for (GameObjManager::iterator i = objs->begin(); i != objs->end(); ++i)
    {
      if (!(*i)->is_hidden())
        (*i)->draw_energie (view);
    }
}

void
GameWorld::draw_levelmap (LevelMap& levelmap)
{
  //groundmap->draw_levelmap (levelmap);

  GameObjManager* objs = game_obj_manager;
  for (GameObjManager::iterator i = objs->begin(); i != objs->end(); ++i)
    {
      if (!(*i)->is_hidden())
        (*i)->draw_levelmap(levelmap);
    }
}

struct is_removable
{
  bool operator() (GameObj* obj)
  {
    return obj->removable ();
  }
};

void
GameWorld::update(float delta)
{
  current_time += delta;

  //wind = FloatVector2d(40.0f).rotate((Math::frand()-.5f) * 5.0f * delta);

  trigger_manager->update(delta);

  game_obj_manager->get_objects().remove_if(is_removable ());

  GameObjManager* objs = game_obj_manager;
  for (GameObjManager::iterator i = objs->begin(); i != objs->end(); ++i)
    if (!(*i)->is_hidden())
      (*i)->update (delta);
}

BuildingMap*
GameWorld::get_buildingmap ()
{
  // FIXME: This is a ugly ugly hack...
  return dynamic_cast<BuildingMap*>(buildingmap);
}

GroundMap*
GameWorld::get_groundmap ()
{
  return groundmap;
}

GameObjManager*
GameWorld::get_game_obj_manager()
{
  return game_obj_manager;
}

FloatVector2d
GameWorld::get_wind() const
{
  return wind;
}

/* EOF */
