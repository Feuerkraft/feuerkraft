//  $Id: handle_manager.hxx,v 1.2 2003/06/06 09:49:00 grumbel Exp $
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

#ifndef HEADER_HANDLE_MANAGER_HXX
#define HEADER_HANDLE_MANAGER_HXX

#include <vector>

/** The HandleManager should take care of objects that get created or
    exported from the Scheme world. The HandleManager should assign an
    uniq id to every object that gets allocated and should allow to
    lookup a object by a given id. Getting the id for a given object
    should also be possible. A Handle and a HandleManager is always
    bound to a specific object type, The HandleManager does not
    provide any way to cleanup at the moment. */
template<class T>
class HandleManager
{
protected:
  typedef std::vector<T*> Objects;
  Objects objects;
public:
  HandleManager() {}
  ~HandleManager() 
  {
    for(typename Objects::iterator i = objects.begin(); i != objects.end(); ++i)
      {
        delete *i;
      }    
  }

  typedef int Handle;

  T* create()
  {
    T* obj = new T();
    objects.push_back(obj);
    return obj;
  }
  
  template<class Arg1>
  T* create(const Arg1& arg1)
  {
    T* obj = new T(arg1);
    objects.push_back(obj);
    return obj;
  }

  template<class Arg1, class Arg2>
  T* create(const Arg1& arg1, const Arg2& arg2)
  {
    T* obj = new T(arg1, arg2);
    objects.push_back(obj);
    return obj;
  }

  
  T* lookup_by_handle(Handle handle)
  {
    if (handle >= 0 && handle < objects.size())
      return objects[handle];
    else
      return 0;    
  }

  Handle lookup_by_object(T* obj)
  {
    for(typename Objects::iterator i = objects.begin(); i != objects.end(); ++i)
      {
        if (*i == obj)
          return i - objects.begin(); // return the index of the object
      }
    return -1;
  }

private:
  HandleManager (const HandleManager&);
  HandleManager& operator= (const HandleManager&);
};

#endif

/* EOF */
