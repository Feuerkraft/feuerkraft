// Feuerkraft - A Tank Battle Game
// Copyright (C) 2002 Ingo Ruhnke <grumbel@gmx.de>
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

#include <assert.h>
#include "property.hpp"
#include "property_set.hpp"

PropertySet::PropertySet()
{

}

PropertySet::~PropertySet()
{
  for(Properties::iterator i = properties.begin(); i != properties.end(); ++i)
    {
      delete i->second;
    }
}

Property*
PropertySet::lookup(const std::string& name)
{
  Properties::iterator i = properties.find(name);
  if (i == properties.end())
    return 0;
  else
    return i->second;
}

void
PropertySet::register_bool(const std::string& name, bool* value_ptr)
{
  assert(lookup(name) == 0);
  properties[name] = new Property(name, value_ptr);
}

void
PropertySet::register_int(const std::string& name, int* value_ptr)
{
  assert(lookup(name) == 0);
  properties[name] = new Property(name, value_ptr);
}

void
PropertySet::register_float(const std::string& name, float* value_ptr)
{
  assert(lookup(name) == 0);
  properties[name] = new Property(name, value_ptr);
}

void
PropertySet::register_string(const std::string& name, std::string* value_ptr)
{
  assert(lookup(name) == 0);
  properties[name] = new Property(name, value_ptr);
}

void
PropertySet::set_bool(const std::string& name, bool value)
{
  Property* property = lookup(name);
  assert(property);
  property->set_bool(value);
}

void
PropertySet::set_int(const std::string& name, int value)
{
  Property* property = lookup(name);
  assert(property);
  property->set_int(value);
}

void
PropertySet::set_float(const std::string& name, float value)
{
  Property* property = lookup(name);
  assert(property);
  property->set_float(value);
}

void
PropertySet::set_string(const std::string& name, const std::string& value)
{
  Property* property = lookup(name);
  assert(property);
  property->set_string(value);

}

/* EOF */
