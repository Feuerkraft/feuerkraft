//  $Id: property.cxx,v 1.1 2003/05/11 11:20:44 grumbel Exp $
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

#include "property.hxx"

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
  assert(type == T_INT);
  *data.m_int = value;
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
Property::get_bool()
{
  assert(type == T_BOOL);
  return *data.m_bool;
}

int
Property::get_int()
{
  assert(type == T_INT);
  return *data.m_int;
}

float
Property::get_float()
{
  assert(type == T_FLOAT);
  return *data.m_float;
}

std::string
Property::get_string()
{
  assert(type == T_STRING);
  return *data.m_string;
}

/* EOF */
