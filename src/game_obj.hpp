// Feuerkraft - A Tank Battle Game
// Copyright (C) 2000 Ingo Ruhnke <grumbel@gmx.de>
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

#ifndef GAMEOBJ_HH
#define GAMEOBJ_HH

#include <assert.h>
#include "game_world.hpp"

class Building;
class Radar;
class View;
class LevelMap;
class GameWorld;
class GameObjData;
class PropertySet;

class GameObj
{
protected:
  friend class GameWorld;

  int id;

  bool hidden;
  bool remove_me;

  friend class GameObjManager;
  void set_id(int i) { id = i; }

  PropertySet* properties;
public:
  GameObj();
  virtual ~GameObj ();

  /** @return the id of the GameObj, this must only be called after
      the GameObj has been added to a GameWorld/GameObjManager,
      calling it before will raise an assertion. */
  int get_id() const { assert(id != -1); return id; }

  PropertySet* get_properties() { return properties; }

  /** This is called once somebody alters the properties, might be
      needed if one for example changes the surface-string and
      requires the surface to be reloaded.

      FIXME: Might be a stupid way to do it, a surface with self
      reloading capabilities might be better, but might not always
      work. */
  virtual void properties_updated() {}

  /** Draw the object onto the main view, which means the object will
      be drawn in normal game grafic */
  virtual void draw(View& view) =0;

  /** Draw the energie bar, this is done in a seperate function to
      avoid rotation and scaling of the energie bar */
  virtual void draw_energie(View& view) {}

  /** Draw the object to the radar */
  virtual void draw_radar (Radar& radar) {}

  /** Draw the object to the levelmap, the levelmap gives an overview
      about the complete level */
  virtual void draw_levelmap(LevelMap& view) {}

  /** Update the object once a game loop */
  virtual void update (float) {}

  /** Mark the object as removable */
  void remove() { remove_me = true; }

  /** Hides an object by removing it from the list of active word
      objects. Hidden objects are not shown and not updated. You can
      unhide an object by calling \a show(). */
  void hide() { hidden = true; }

  /** Shows a hidden object */
  void show() { hidden = false; }

  /** @return true if an object is hidden */
  bool is_hidden() const { return hidden; }

  // @return true if the object can be removed from the world
  virtual bool removable () { return remove_me; }

  virtual void on_collision(GameObj* obj);
  virtual void on_collision_with_building(Building* building);

  //
  virtual float get_z_pos () { return 0; }

  /* Stuff that is used for the radar and probally for physics later
     on */
  virtual float get_physical_mass () { return 1.0; }
  virtual float get_physical_size () { return 1.0; }

private:
  GameObj(const GameObj&);
  GameObj& operator=(const GameObj&);
};

typedef GameObj* GameObjPtr;

#endif

/* EOF */
