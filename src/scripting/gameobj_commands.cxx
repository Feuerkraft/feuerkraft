//  $Id: gameobj_commands.cxx,v 1.2 2003/05/11 19:50:37 grumbel Exp $
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

#include "../guile.hxx"
#include "../property_set.hxx"
#include "../property.hxx"
#include "../game_obj.hxx"
#include "../game_obj_manager.hxx"
#include "gameobj_commands.hxx"

SCM
gameobj_get_property(int handle, const char* name)
{
  GameObj* obj = GameObjManager::current()->get_object_by_id(handle);
  if (obj)
    {
      PropertySet* properties = obj->get_properties();
      if (properties)
        {
          Property* prop = properties->lookup(name);
          if (prop)
            return Guile::property2scm(*prop);
        }
    }
    
  return SCM_UNSPECIFIED;
}

void
gameobj_set_property(int handle, const char* name, SCM value)
{
  GameObj* obj = GameObjManager::current()->get_object_by_id(handle);
  if (obj)
    {
      PropertySet* properties = obj->get_properties();
      if (properties)
        {
          Guile::scm2property(*properties, name, value);
        }      
    }
}

SCM
gameobj_properties(int handle)
{
  GameObj* obj = GameObjManager::current()->get_object_by_id(handle);
  
  if (obj)
    {
      SCM lst = SCM_EOL;
      PropertySet* properties = obj->get_properties();

      if (properties)
        {
          for (PropertySet::iterator i = properties->begin();
               i != properties->end();
               ++i)
            {
              lst = gh_cons(gh_str02scm(i->second->get_name().c_str()), lst);
            }
        }
      return gh_reverse(lst);
    }
  return SCM_BOOL_F;
}

/* EOF */
