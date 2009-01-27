//  $Id: game_obj_factory.cxx,v 1.10 2003/06/22 17:22:47 grumbel Exp $
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

#include <iostream>
#include "property_set.hxx"

// GameObjs
#include "vehicles/tank.hxx"
#include "vehicles/helicopter.hxx"
#include "tree.hxx"
#include "marker.hxx"
#include "mine.hxx"
#include "soldier.hxx"
#include "satchel_charge.hxx"

#include "game_obj.hxx"
#include "game_obj_factory.hxx"

GameObjFactory* GameObjFactory::instance_ = 0;

GameObjFactory::GameObjFactory()
{
  // If anything is changed here, make sure to update
  // data/feuerkraft.scm

  // FIXME: Types should be named here, to not having update to files
  register_factory("none",       0); // id=0 -> the empty factory
  register_factory("tree",       new GameObjGenericFactory<Tree>());
  register_factory("marker",     new GameObjGenericFactory<Marker>());
  register_factory("mine",       new GameObjGenericFactory<Mine>());
  register_factory("satchel",    new GameObjGenericFactory<SatchelCharge>());
  register_factory("soldier",    new GameObjGenericFactory<Soldier>());
  register_factory("tank",       new GameObjGenericFactory<Tank>());
  register_factory("helicopter", new GameObjGenericFactory<Helicopter>());
}

GameObjFactory* 
GameObjFactory::instance()
{
  if (instance_)
    return instance_;
  else
    return (instance_ = new GameObjFactory());
}

GameObj*
GameObjFactory::create(int type_id, const AList& alst)
{
  GameObj* obj = create_raw_object(type_id, alst);

  if (obj)
    {
      // FIXME: All this should be no longer needed if objects get the AList
      // as constructor
#if 0      
      PropertySet* props = obj->get_properties();

      for (AList::const_iterator i = alst.begin(); i != alst.end(); ++i)
        {
          //std::cout << ">>># " << i->second.type << std::endl;
          
          switch(i->second.type)
            {
            case AList::AL_INT:
              props->set_int(i->first, i->second.v_int);
              break;
            case AList::AL_FLOAT:
              props->set_float(i->first, i->second.v_float);
              break;
            case AList::AL_STRING:
              props->set_string(i->first, *i->second.v_string);
              break;
            case AList::AL_BOOL:
              props->set_bool(i->first, i->second.v_bool);
              break;
            default:
              std::cout << "GameObjFactory: Unhandled property" << std::endl;
            }
        }

      obj->properties_updated();
#endif
    }

  return obj;
}

GameObj* 
GameObjFactory::create_raw_object(int type_id, const AList& lst)
{
  GameObjAbstractFactory* factory = get_factory(type_id);

  if (factory)
    return factory->create(lst);
  else
    return 0;
}

GameObjAbstractFactory*
GameObjFactory::get_factory(int type_id)
{
  if (type_id >= 0 && type_id < int(factories.size()))
    return factories[type_id];
  else 
    return 0;
}

int
GameObjFactory::register_factory(const char* name, GameObjAbstractFactory* factory)
{
  int type_id = factories.size();
  factories.push_back(factory);
  return type_id;
}

/* EOF */
