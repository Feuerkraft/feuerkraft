//  $Id: alist.cxx,v 1.1 2003/05/09 14:30:10 grumbel Exp $
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

#include "string_converter.hxx"
#include "alist.hxx"

void
AList::set_int(const std::string& name, int value)
{
  content[name] = to_string(value);
}

void
AList::set_bool(const std::string& name, bool value)
{
  content[name] = to_string(value);
}

void
AList::set_string(const std::string& name, const std::string& value)
{
  content[name] = value;
}

bool
AList::get_int(const std::string& name, int& value) const
{
  Content::const_iterator i = content.find(name);

  if (i == content.end())
    return false;
  else
    {
      return from_string(i->second, value);
    }
}

bool
AList::get_bool(const std::string& name, bool& value) const
{
  Content::const_iterator i = content.find(name);
  if (i == content.end())
    return false;
  else
    {
      return from_string(i->second, value);
    }
}

bool
AList::get_string(const std::string& name, std::string& value) const
{
  Content::const_iterator i = content.find(name);
  if (i == content.end())
    return false;
  else
    {
      value = i->second;
      return true;
    }
}

/* EOF */
