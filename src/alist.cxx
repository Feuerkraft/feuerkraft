//  $Id: alist.cxx,v 1.6 2003/05/13 17:30:27 grumbel Exp $
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
#include "string_converter.hxx"
#include "alist.hxx"

AList::AList()
{  
}

AList::AList(const AList& alist)
{
  content = alist.content;

  for(Content::iterator i = content.begin(); i != content.end(); ++i)
    {
      if (i->second.type == AL_STRING)
        i->second.value.v_string = new std::string(*(i->second.value.v_string));
    }
}

AList&
AList::operator=(const AList& alist)
{
  for(Content::iterator i = content.begin(); i != content.end(); ++i)
    {
      if (i->second.type == AL_STRING)
        delete i->second.value.v_string;
    }
  content.clear();

  content = alist.content;

  for(Content::iterator i = content.begin(); i != content.end(); ++i)
    {
      if (i->second.type == AL_STRING)
        i->second.value.v_string = new std::string(*(i->second.value.v_string));
    }
  return *this;
}

AList::~AList()
{
  for(Content::iterator i = content.begin(); i != content.end(); ++i)
    {
      if (i->second.type == AL_STRING)
        delete i->second.value.v_string;
    }
}

AList::Value&
AList::ensure_free_cell(const std::string& name, Type type)
{
  Value& value = content[name];
  if (value.type == AL_STRING)
    delete value.value.v_string;
  
  if (value.type != type && value.type != AL_NONE)
    {
      std::cout << "AList: Warning: Overwriting cell: " << name << " with other type." << std::endl;
    }
  value.type = type;
  
  return value;
}

AList::AList&
AList::set_int(const std::string& name, int value)
{
  Value& v = ensure_free_cell(name, AL_INT);
  v.value.v_int = value;
  return *this;
}

AList&
AList::set_float(const std::string& name, float value)
{
  Value& v = ensure_free_cell(name, AL_FLOAT);
  v.value.v_float = value;
  return *this;
}

AList&
AList::set_bool(const std::string& name, bool value)
{
  Value& v = ensure_free_cell(name, AL_BOOL);
  v.value.v_bool = value;
  return *this;
}

AList&
AList::set_string(const std::string& name, const std::string& value)
{
  std::cout << "AList: " << name << " '" << value << "'" << std::endl;
  Value& v = ensure_free_cell(name, AL_STRING);
  v.value.v_string = new std::string(value);
  return *this;
}

AList&
AList::set_int_vector2d(const std::string& name, IntVector2d& value)
{
  Value& v = ensure_free_cell(name, AL_INTVECTOR2D);
  v.value.v_int_vector2d = value;
  return *this;
}

AList&
AList::set_float_vector2d(const std::string& name, FloatVector2d& value)
{
  Value& v = ensure_free_cell(name, AL_FLOATVECTOR2D);
  v.value.v_float_vector2d = value;  
  return *this;
}

const AList::Value*
AList::get_value(const std::string& name, Type type) const
{
  Content::const_iterator i = content.find(name);

  if (i == content.end())
    {
      return 0;
    }
  else
    {
      if (i->second.type == type)
        return &(i->second);
      else
        return 0;
    } 
}

bool
AList::get_int(const std::string& name, int& value) const
{
  const Value* v = get_value(name, AL_INT);

  if (!v)
    return false;
  else
    {
      value = v->value.v_int;
      return true;
    }
}

bool
AList::get_float(const std::string& name, float& value) const
{
  const Value* v = get_value(name, AL_FLOAT);
  if (!v)
    {
      const Value* int_v = get_value(name, AL_INT);
      if (int_v)
        {
          value = int_v->value.v_int;
          return true;
        }
      else
        return false;
    }
  else
    {
      value = v->value.v_float;
      return true;
    }
}

bool
AList::get_bool(const std::string& name, bool& value) const
{
  const Value* v = get_value(name, AL_BOOL);
  if (!v)
    return false;
  else
    {
      value = v->value.v_bool;
      return true;
    }
}

bool
AList::get_string(const std::string& name, std::string& value) const
{
  const Value* v = get_value(name, AL_STRING);
  if (v == 0)
    return false;
  else
    {
      value = *(v->value.v_string);
      return true;
    }
}

bool
AList::get_int_vector2d (const std::string& name, IntVector2d& value) const
{
  const Value* v = get_value(name, AL_INTVECTOR2D);
  if (!v)
    return false;
  else
    {
      value = v->value.v_int_vector2d;
      return true;
    }
}

bool
AList::get_float_vector2d (const std::string& name, FloatVector2d& value) const
{
  const Value* v = get_value(name, AL_FLOATVECTOR2D);
  if (!v)
    return false;
  else
    {
      value = v->value.v_float_vector2d;
      return true;
    }
}

/* EOF */
