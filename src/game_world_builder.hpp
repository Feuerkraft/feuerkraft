//  $Id: game_world_builder.hpp,v 1.2 2003/06/03 14:11:22 grumbel Exp $
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

#ifndef HEADER_GAME_WORLD_BUILDER_HXX
#define HEADER_GAME_WORLD_BUILDER_HXX

#include "world_builder.hpp"

class GameWorld;

/** */
class GameWorldBuilder
  : public WorldBuilder
{
private:
  GameWorld* world;

public:
  GameWorldBuilder();
  ~GameWorldBuilder();

  void add_object(const std::string& type, const AList&);
  void add_brush(const std::string& resname, const AList&);
  void add_building(const std::string&, const AList&);
  void add_groundmap(const std::string&, const AList&);
  void add_script(const std::string& resname);

  /** @return the created world, must only called once! */
  GameWorld* get_world();
private:
  GameWorldBuilder (const GameWorldBuilder&);
  GameWorldBuilder& operator= (const GameWorldBuilder&);
};

#endif

/* EOF */
