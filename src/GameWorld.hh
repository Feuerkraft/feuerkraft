//  $Id: GameWorld.hh,v 1.3 2001/02/18 20:16:50 grumbel Exp $
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
#include "GameObj.hh"

class GameObj;

class GameWorld
{
private:
  std::list<boost::shared_ptr<GameObj> > objects;
  
public:
  GameWorld ();
  ~GameWorld ();
  
  /// Return a reference to the objects in the world
  std::list<boost::shared_ptr<GameObj> >& get_objects () { return objects; }
  void add (boost::shared_ptr<GameObj>);
  void add (GameObj*);

  void draw ();
  void update ();
};

#endif

/* EOF */
