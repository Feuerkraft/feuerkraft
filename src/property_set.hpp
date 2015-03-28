//  $Id: property_set.hpp,v 1.4 2003/06/03 14:11:22 grumbel Exp $
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

#ifndef HEADER_FEUERKRAFT_PROPERTY_SET_HXX
#define HEADER_FEUERKRAFT_PROPERTY_SET_HXX

#include <map>
#include <string>

class Property;

/** */
class PropertySet
{
private:
  typedef std::map<std::string, Property*>  Properties;
  Properties properties;
public:
  typedef Properties::iterator iterator;
  typedef Properties::const_iterator const_iterator;

  PropertySet();
  ~PropertySet();

  void register_bool  (const std::string& name, bool* value_ptr);
  void register_int   (const std::string& name, int* value_ptr);
  void register_float (const std::string& name, float* value_ptr);
  void register_string(const std::string& name, std::string* value_ptr);

  void set_bool  (const std::string& name, bool value);
  void set_int   (const std::string& name, int value);
  void set_float (const std::string& name, float value);
  void set_string(const std::string& name, const std::string& value);

  Property* lookup(const std::string& name);

  const_iterator begin() const { return properties.begin(); }
  const_iterator end()   const { return properties.end(); }

  iterator begin(){ return properties.begin(); }
  iterator end()  { return properties.end(); }
private:
  Property& create_property(const std::string& name);

  PropertySet (const PropertySet&);
  PropertySet& operator= (const PropertySet&);
};

#endif

/* EOF */
