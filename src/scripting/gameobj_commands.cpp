// Feuerkraft - A Tank Battle Game
// Copyright (C) 2002 Ingo Ruhnke <grumbel@gmail.com>
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

#include "../guile.hpp"
#include "../property_set.hpp"
#include "../property.hpp"

#include "../satchel_charge.hpp"
#include "../soldier.hpp"
#include "../vehicles/vehicle.hpp"
#include "../vehicles/helicopter.hpp"
#include "../unit.hpp"

#include "../game_obj.hpp"
#include "../game_obj_manager.hpp"
#include "../game_obj_factory.hpp"
#include "gameobj_commands.hpp"

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
              lst = scm_cons(scm_from_utf8_string(i->second->get_name().c_str()), lst);
            }
        }
      return scm_reverse(lst);
    }
  return SCM_BOOL_F;
}

int
gameobj_create(int type_id, SCM lst)
{
  GameObj* obj = GameObjFactory::instance()->create(type_id, Guile::scm2alist(lst));
  if (obj)
    return GameObjManager::current()->add_object(obj);
  else
    return 0;
}

void
gameobj_remove(int handle)
{
  GameObj* obj = GameObjManager::current()->get_object_by_id(handle);
  if (obj)
    obj->remove();
}

bool
gameobj_is_vehicle(int handle)
{
  GameObj* obj = GameObjManager::current()->get_object_by_id(handle);
  return (obj && dynamic_cast<Vehicle*>(obj));
}

bool
gameobj_is_unit(int handle)
{
  GameObj* obj = GameObjManager::current()->get_object_by_id(handle);
  return (obj && dynamic_cast<Unit*>(obj));
}

bool
gameobj_is_soldier(int handle)
{
  GameObj* obj = GameObjManager::current()->get_object_by_id(handle);
  return (obj && dynamic_cast<Soldier*>(obj));
}

bool
gameobj_is_helicopter(int handle)
{
  GameObj* obj = GameObjManager::current()->get_object_by_id(handle);
  return (obj && dynamic_cast<Helicopter*>(obj));
}

void
satchel_detonate(int handle)
{
  GameObj* obj = GameObjManager::current()->get_object_by_id(handle);
  if (obj)
    {
      SatchelCharge* satchel = dynamic_cast<SatchelCharge*>(obj);
      if (satchel)
        satchel->detonate();
    }
}

SCM
gameobj_get_all()
{
  SCM lst = SCM_EOL;

  for (GameObjManager::iterator i = GameObjManager::current()->begin();
       i != GameObjManager::current()->end();
       ++i)
    {
      lst = scm_cons(scm_from_long((*i)->get_id()), lst);
    }

  return scm_reverse(lst);
}

/* EOF */
