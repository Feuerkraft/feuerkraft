//  $Id: property_set.hxx,v 1.2 2003/05/11 17:06:11 grumbel Exp $
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

#ifndef HEADER_PROPERTY_SET_HXX
#define HEADER_PROPERTY_SET_HXX

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
