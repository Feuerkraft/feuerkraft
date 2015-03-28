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

#ifndef HEADER_WORLD_BUILDER_HXX
#define HEADER_WORLD_BUILDER_HXX

#include "alist.hpp"

/** */
class WorldBuilder
{
private:
public:
  WorldBuilder() {}
  virtual ~WorldBuilder() {}

  virtual void add_object(const std::string& type, const AList&) =0;
  virtual void add_brush(const std::string& resname, const AList&) =0;
  virtual void add_building(const std::string&, const AList&) =0;
  virtual void add_groundmap(const std::string&, const AList&) =0;
  virtual void add_script(const std::string& resname) =0;

private:
  WorldBuilder (const WorldBuilder&);
  WorldBuilder& operator= (const WorldBuilder&);
};

#endif

/* EOF */
