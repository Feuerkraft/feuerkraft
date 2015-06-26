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

#include <iostream>
#include <assert.h>
#include <ClanLib/Core/System/clanstring.h>
#include "property.hpp"

Property::Property(const std::string& arg_name)
  : name(arg_name), type(T_EMPTY)
{
}

Property::Property(const std::string& arg_name, bool* value_ptr)
  : name(arg_name), type(T_BOOL)
{
  data.m_bool = value_ptr;
}

Property::Property(const std::string& arg_name, int* value_ptr)
  : name(arg_name), type(T_INT)
{
  data.m_int = value_ptr;
}

Property::Property(const std::string& arg_name, float* value_ptr)
  : name(arg_name), type(T_FLOAT)
{
  data.m_float = value_ptr;
}

Property::Property(const std::string& arg_name, std::string* value_ptr)
  : name(arg_name), type(T_STRING)
{
  data.m_string = value_ptr;
}

Property::~Property()
{
}

void
Property::set_bool(bool value)
{
  assert(type == T_BOOL);
  *data.m_bool = value;
}

void
Property::set_int(int value)
{
  assert(type == T_INT || type == T_EMPTY);
  *data.m_int = value;
  type = T_INT;
}

void
Property::set_float(float value)
{
  assert(type == T_FLOAT);
  *data.m_float = value;
}

void
Property::set_string(const std::string& value)
{
  assert(type == T_STRING);
  *data.m_string = value;
}

bool
Property::get_bool() const
{
  assert(type == T_BOOL);
  return *data.m_bool;
}

int
Property::get_int() const
{
  assert(type == T_INT);
  return *data.m_int;
}

float
Property::get_float() const
{
  assert(type == T_FLOAT);
  return *data.m_float;
}

std::string
Property::get_string() const
{
  assert(type == T_STRING);
  return *data.m_string;
}

std::string
Property::to_string() const
{
  switch (type)
    {
    case Property::T_BOOL:
      return CL_String::to(get_bool());

    case Property::T_FLOAT:
      return CL_String::to(get_float());

    case Property::T_INT:
      return CL_String::to(get_int());

    case Property::T_STRING:
      return get_string();

    default:
      return "<empty>";
    }
}

std::ostream& operator<<(std::ostream& s, const Property& property)
{
  switch (property.type)
    {
    case Property::T_BOOL:
      return s << property.get_bool();

    case Property::T_FLOAT:
      return s << property.get_float();

    case Property::T_INT:
      return s << property.get_int();

    case Property::T_STRING:
      return s << property.get_string();

    default:
      return s << "<empty>";
    }
}

/* EOF */
