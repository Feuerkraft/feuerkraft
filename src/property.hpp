//  $Id: property.hpp,v 1.5 2003/06/03 14:11:22 grumbel Exp $
// 
//  Feuerkraft - A Tank Battle Game
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

#ifndef HEADER_PROPERTY_HXX
#define HEADER_PROPERTY_HXX

#include <string>

/** A Property is a generic objects which can hold data of most
    primitive data types */
class Property
{
public:
  enum Type {
    T_EMPTY, T_BOOL, T_INT, T_FLOAT, T_STRING
  };

protected:
  union Data {
    bool*        m_bool;
    int*         m_int;
    float*       m_float;
    std::string* m_string;
  };
 
  std::string name;
  Type type;
  Data data;

public:
  Property(const std::string& name);
  Property(const std::string& name, bool*);
  Property(const std::string& name, int*);
  Property(const std::string& name, float*);
  Property(const std::string& name, std::string*);
  ~Property();

  void set_name(const std::string& arg_name) { name = arg_name; }
  std::string get_name() const { return name; }

  Type get_type() const { return type; }
  
  void set_bool(bool);
  void set_int(int);
  void set_float(float);
  void set_string(const std::string&);

  bool  get_bool() const;
  int   get_int()  const;
  float get_float() const;
  std::string get_string() const;

  /** @return the value of the property as string. If it is not a
      T_STRING, it is converted to a string on return */
  std::string to_string() const;

  friend std::ostream& operator<<(std::ostream& s, const Property& property);
};

std::ostream& operator<<(std::ostream& s, const Property& property);

#endif

/* EOF */
