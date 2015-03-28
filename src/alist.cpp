//  $Id: alist.cpp,v 1.13 2003/06/23 08:43:32 grumbel Exp $
//
//  Feuerkraft - A Tank Battle Game
//  Copyright (C) 2002 Ingo Ruhnke <grumbel@gmx.de>
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include <iostream>
#include "alist.hpp"

AList::AList()
{
}

AList::AList(const AList& alist)
{
  content = alist.content;

  for(Content::iterator i = content.begin(); i != content.end(); ++i)
    {
      if (i->second.type == AL_STRING)
        i->second.v_string = new std::string(*(i->second.v_string));
    }
}

AList&
AList::operator=(const AList& alist)
{
  for(Content::iterator i = content.begin(); i != content.end(); ++i)
    {
      if (i->second.type == AL_STRING)
        delete i->second.v_string;
    }
  content.clear();

  content = alist.content;

  for(Content::iterator i = content.begin(); i != content.end(); ++i)
    {
      if (i->second.type == AL_STRING)
        i->second.v_string = new std::string(*(i->second.v_string));
    }
  return *this;
}

AList::~AList()
{
  for(Content::iterator i = content.begin(); i != content.end(); ++i)
    {
      if (i->second.type == AL_STRING)
        delete i->second.v_string;
    }
}

AList::Value&
AList::ensure_free_cell(const std::string& name, Type type)
{
  Value& value = content[name];
  if (value.type == AL_STRING)
    delete value.v_string;

  if (value.type != type && value.type != AL_NONE)
    {
      std::cout << "AList: Warning: Overwriting cell: " << name << " with other type." << std::endl;
    }
  value.type = type;

  return value;
}

AList&
AList::set_int(const std::string& name, int value)
{
  Value& v = ensure_free_cell(name, AL_INT);
  v.v_int = value;
  return *this;
}

AList&
AList::set_float(const std::string& name, float value)
{
  Value& v = ensure_free_cell(name, AL_FLOAT);
  v.v_float = value;
  return *this;
}

AList&
AList::set_bool(const std::string& name, bool value)
{
  Value& v = ensure_free_cell(name, AL_BOOL);
  v.v_bool = value;
  return *this;
}

AList&
AList::set_string(const std::string& name, const std::string& value)
{
  //std::cout << "AList: " << name << " '" << value << "'" << std::endl;
  Value& v = ensure_free_cell(name, AL_STRING);
  v.v_string = new std::string(value);
  return *this;
}

AList&
AList::set_int_vector2d(const std::string& name, IntVector2d& value)
{
  Value& v = ensure_free_cell(name, AL_INTVECTOR2D);
  v.v_int_vector2d = value;
  return *this;
}

AList&
AList::set_value (const std::string& str, const Value& value)
{
  switch (value.type)
    {
    case AL_INT:
      return set_int(str, value.v_int);

    case AL_FLOAT:
      return set_float(str, value.v_float);

    case AL_BOOL:
      return set_bool(str, value.v_bool);

    case AL_STRING:
      return set_string(str, *value.v_string);

    default:
      return *this;
    }
}

/*
  AList&
  AList::set_float_vector2d(const std::string& name, FloatVector2d& value)
  {
  Value& v = ensure_free_cell(name, AL_FLOATVECTOR2D);
  v.v_float_vector2d = value;
  return *this;
  }
*/
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
AList::retrieve_int(const std::string& name, int& value) const
{
  const Value* v = get_value(name, AL_INT);

  if (!v)
    return false;
  else
    {
      value = v->v_int;
      return true;
    }
}

bool
AList::retrieve_float(const std::string& name, float& value) const
{
  const Value* v = get_value(name, AL_FLOAT);
  if (!v)
    {
      const Value* int_v = get_value(name, AL_INT);
      if (int_v)
        {
          value = int_v->v_int;
          return true;
        }
      else
        return false;
    }
  else
    {
      value = v->v_float;
      return true;
    }
}

bool
AList::retrieve_bool(const std::string& name, bool& value) const
{
  const Value* v = get_value(name, AL_BOOL);
  if (!v)
    return false;
  else
    {
      value = v->v_bool;
      return true;
    }
}

bool
AList::retrieve_string(const std::string& name, std::string& value) const
{
  const Value* v = get_value(name, AL_STRING);
  if (v == 0)
    return false;
  else
    {
      value = *(v->v_string);
      return true;
    }
}

bool
AList::retrieve_int_vector2d (const std::string& name, IntVector2d& value) const
{
  const Value* v = get_value(name, AL_INTVECTOR2D);
  if (!v)
    return false;
  else
    {
      value = v->v_int_vector2d;
      return true;
    }
}

bool
AList::retrieve_float_vector2d (const std::string& name, FloatVector2d& value) const
{
  return false;
  /*
  const Value* v = get_value(name, AL_FLOATVECTOR2D);
  if (!v)
    return false;
  else
    {
      value = v->v_float_vector2d;
      return true;
      }*/
}

int
AList::get_int(const std::string& str, int def) const
{
  int res;
  if (retrieve_int(str, res))
    return res;
  else
    return def;
}

float
AList::get_float(const std::string& str, float def) const
{
  float res;
  if (retrieve_float(str, res))
    return res;
  else
    return def;
}

bool
AList::get_bool(const std::string& str, bool def) const
{
  bool res;
  if (retrieve_bool(str, res))
    return res;
  else
    return def;
}

std::string
AList::get_string(const std::string& str, const std::string& def) const
{
  std::string res;
  if (retrieve_string(str, res))
    return res;
  else
    return def;
}

void
AList::merge(const AList& lst)
{
  for(Content::const_iterator i = lst.content.begin(); i != lst.content.end(); ++i)
    {
      set_value(i->first, i->second);
    }
}

/*
  bool
  AList::get_float_vector2d (const std::string& name, FloatVector2d& value) const
  {
  const Value* v = get_value(name, AL_FLOATVECTOR2D);
  if (!v)
  return false;
  else
  {
  value = v->v_float_vector2d;
  return true;
  }
  }
*/

std::ostream& operator<< (std::ostream& os, const AList& lst)
{
  os << "[AList:]\n";
  for(AList::const_iterator i = lst.begin(); i != lst.end(); ++i)
    {
      os << "  " << i->first << " -> " << i->second << std::endl;
    }
  os << std::endl;
  return os;
}

std::ostream& operator<< (std::ostream& os, const AList::Value& value)
{
  switch (value.type)
    {
    case AList::AL_INT:
      return os << value.v_int;

    case AList::AL_FLOAT:
      return os << value.v_float;

    case AList::AL_BOOL:
      return os << value.v_bool;

    case AList::AL_STRING:
      return os << *value.v_string;

    default:
      return os << "<#unknown>>";
    }
}

/* EOF */
