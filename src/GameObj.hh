//  $Id: GameObj.hh,v 1.8 2001/05/01 10:44:54 grumbel Exp $
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

#include "View.hh"
#include "GameWorld.hh"

class View;
class GameWorld;

class GameObj
{
protected:
  friend class GameWorld;

  GameWorld* world;
  bool remove_me;
public:
  
  GameObj () : remove_me (false) {}
  virtual ~GameObj () {}

  void set_world (GameWorld* w) { 
    world = w; 
  }
  
  GameWorld* get_world () {
    return world; 
  }

  // Draw the object onto the screen
  virtual void draw (View* view) =0;
  
  // Update the object once a game loop
  virtual void update (float) {}

  // Mark the object as removable
  virtual void remove () { remove_me = true; }

  // @return true if the object can be removed from the world
  virtual bool removable () { return remove_me; }

  //
  virtual int  get_z_pos () { return 0; }

  /* Stuff that is used for the radar and probally for physics later
     on */
  virtual float get_physical_mass () { return 1.0; }
  virtual float get_physical_size () { return 1.0; }

  // This is a pseudo constructor which is called when the world pointer is set
  virtual void init () {}
};

#endif

/* EOF */
