//  $Id: game_obj_factory.cxx,v 1.2 2003/05/18 21:15:06 grumbel Exp $
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

#include <iostream>
#include "property_set.hxx"
#include "tree.hxx"
#include "game_obj.hxx"
#include "game_obj_factory.hxx"

GameObjFactory* GameObjFactory::instance_ = 0;

GameObjFactory::GameObjFactory()
{
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
  GameObj* obj = create_raw_object(type_id);

  if (obj)
    {
      PropertySet* props = obj->get_properties();
      
      for (AList::const_iterator i = alst.begin(); i != alst.end(); ++i)
        {
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
    }

  return obj;
}

GameObj* 
GameObjFactory::create_raw_object(int type_id)
{
  return new Tree();
}

/* EOF */
