//  $Id: game_obj.hxx,v 1.2 2003/04/19 23:17:52 grumbel Exp $
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

#ifndef GAMEOBJ_HH
#define GAMEOBJ_HH

#include "view.hxx"
#include "boost/dummy_ptr.hpp"
#include "game_world.hxx"

class Radar;
class View;
class LevelMap;
class GameWorld;
class GameObjData;

class GameObj
{
protected:
  friend class GameWorld;

  boost::dummy_ptr<GameWorld> world;
  bool remove_me;
public:
  
  GameObj (boost::dummy_ptr<GameWorld>  w)
    : world (w),
      remove_me (false) {}

  virtual ~GameObj () {}

  /** Sync the GameObj with its GameObjData parent and return a
      pointer to the parent. The parent must not be deleted.
      0 is return if the function is unimplemented. */
  virtual GameObjData* get_data () { return 0; }

  boost::dummy_ptr<GameWorld> get_world () {
    return world; 
  }

  /** Draw the object onto the main view, which means the object will
      be drawn in normal game grafic */
  virtual void draw (View* view) =0;

  /** Draw the energie bar, this is done in a seperate function to
      avoid rotation and scaling of the energie bar */
  virtual void draw_energie (View* view) {}

  /** Draw the object to the radar */
  virtual void draw_radar (Radar* radar) {}

  /** Draw the object to the levelmap, the levelmap gives an overview
      about the complete level */
  virtual void draw_levelmap (LevelMap* view) {}
  
  // Update the object once a game loop
  virtual void update (float) {}

  // Mark the object as removable
  virtual void remove () { remove_me = true; }

  // @return true if the object can be removed from the world
  virtual bool removable () { return remove_me; }
  
  /** flip is called once after an update step is completly
      finished. This is needed because collision detection is handled
      outsite this gameobject */
  virtual void flip () { /* do nothing */ }

  //
  virtual int  get_z_pos () { return 0; }

  /* Stuff that is used for the radar and probally for physics later
     on */
  virtual float get_physical_mass () { return 1.0; }
  virtual float get_physical_size () { return 1.0; }
};

#endif

/* EOF */
