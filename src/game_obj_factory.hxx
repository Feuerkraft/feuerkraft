//  $Id: game_obj_factory.hxx,v 1.1 2003/05/18 11:39:00 grumbel Exp $
// 
//  Pingus - A free Lemmings clone
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

#include "alist.hxx"

class GameObj;

/** */
class GameObjFactory
{
private:
  static GameObjFactory* instance_;
  GameObjFactory();
public:
  static GameObjFactory* instance();

  GameObj* create(int type_id, const AList& alist);
private:
  GameObj* create_raw_object(int type_id);

  GameObjFactory (const GameObjFactory&);
  GameObjFactory& operator= (const GameObjFactory&);
};

#endif

/* EOF */
