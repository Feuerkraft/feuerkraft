//  $Id: game_obj_factory.hxx,v 1.5 2003/06/22 17:22:47 grumbel Exp $
// 
//  Feuerkraft - A Tank Battle Game
//  Copyright (C) 2002 Ingo Ruhnke <grumbel@gmx.de>
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

#ifndef HEADER_GAME_OBJ_FACTORY_HXX
#define HEADER_GAME_OBJ_FACTORY_HXX

#include <vector>
#include "alist.hxx"

class GameObj;

class GameObjAbstractFactory
{
public:
  virtual GameObj* create(const AList& lst) =0;
};

template<class T>
class GameObjGenericFactory : public GameObjAbstractFactory
{
public:
  GameObj* create(const AList& lst) { return new T(lst); }
};

/** */
class GameObjFactory
{
private:
  static GameObjFactory* instance_;
  GameObjFactory();
public:
  static GameObjFactory* instance();

private:
  typedef std::vector<GameObjAbstractFactory*> Factories;
  Factories factories;

  GameObjAbstractFactory* get_factory(int type_id);
public:
  GameObj* create(int type_id, const AList& alist);

  /** @return type_id of the newly registered type */
  int register_factory(const char* name, GameObjAbstractFactory* factory);
private:
  GameObj* create_raw_object(int type_id, const AList& lst);

  GameObjFactory (const GameObjFactory&);
  GameObjFactory& operator= (const GameObjFactory&);
};

#endif

/* EOF */
