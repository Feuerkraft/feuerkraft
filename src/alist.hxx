//  $Id: alist.hxx,v 1.2 2003/05/10 22:41:28 grumbel Exp $
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

/** Simple associated list like class */
class AList
{
private:
  typedef std::map<std::string, std::string> Content;
  Content content;
public:
  typedef Content::iterator iterator;
  typedef Content::const_iterator const_iterator;

  AList& set_int(const std::string& str, int);
  AList& set_float(const std::string& str, float);
  AList& set_bool(const std::string& str, bool);
  AList& set_string(const std::string& str, const std::string&);

  bool get_int(const std::string& str, int&) const;
  bool get_float(const std::string& str, float&) const;
  bool get_bool(const std::string& str, bool&) const;
  bool get_string(const std::string& str, std::string&) const;
};

#endif

/* EOF */
