//  $Id: alist.hxx,v 1.3 2003/05/11 11:20:44 grumbel Exp $
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

#ifndef HEADER_ALIST_HXX
#define HEADER_ALIST_HXX

#include <string>
#include <map>
#include "vector2d.hxx"

/** Simple associated list like class */
class AList
{
public:
  enum Type { AL_NONE, AL_INT, AL_FLOAT, AL_BOOL, AL_STRING, AL_INTVECTOR2D, AL_FLOATVECTOR2D };

  struct Value {
    Type type;
    
    union {
      int   v_int;
      float v_float;
      bool  v_bool;
      IntVector2d   v_int_vector2d;
      FloatVector2d v_float_vector2d;
      std::string* v_string;
    } value;
  };
private:
  typedef std::map<std::string, Value> Content;
  Content content;

  Value& ensure_free_cell(const std::string& name, Type type);
  const Value* get_value(const std::string& name, Type type) const;
public:
  typedef Content::iterator iterator;
  typedef Content::const_iterator const_iterator;

  AList();
  ~AList();

  AList& set_int   (const std::string& str, int value);
  AList& set_float (const std::string& str, float value);
  AList& set_bool  (const std::string& str, bool value);
  AList& set_string(const std::string& str, const std::string& value);
  AList& set_int_vector2d(const std::string& str, IntVector2d& value);
  AList& set_float_vector2d(const std::string& str, FloatVector2d& value);

  bool get_int      (const std::string& str, int& value) const;
  bool get_float    (const std::string& str, float&value) const;
  bool get_bool     (const std::string& str, bool& value) const;
  bool get_string   (const std::string& str, std::string& value) const;

  bool get_int_vector2d (const std::string& str, IntVector2d& value) const;
  bool get_float_vector2d (const std::string& str, FloatVector2d& value) const;

  iterator begin() { return content.begin(); }
  iterator end() { return content.end(); }

  const_iterator begin() const { return content.begin(); }
  const_iterator end() const { return content.end(); }
};

#endif

/* EOF */
