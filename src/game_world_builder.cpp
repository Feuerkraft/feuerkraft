// Feuerkraft - A Tank Battle Game
// Copyright (C) 2002 Ingo Ruhnke <grumbel@gmail.com>
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

#include <iostream>
#include "game_world.hpp"
#include "game_world_builder.hpp"

GameWorldBuilder::GameWorldBuilder()
{
  // The allocated GameWorld class is freeded by the caller of get_world()
  //world = new GameWorld();
}

GameWorldBuilder::~GameWorldBuilder()
{
  // Delete the world if get_world() wasn't called
  delete world;
}

void
GameWorldBuilder::add_object (const std::string& type, const AList&)
{

}

void
GameWorldBuilder::add_brush(const std::string& resname, const AList&)
{

}

void
GameWorldBuilder::add_building(const std::string& type, const AList&)
{

}

void
GameWorldBuilder::add_groundmap(const std::string& type, const AList&)
{

}

void
GameWorldBuilder::add_script(const std::string& resname)
{
  std::cout << "### Loading Script: " << resname << std::endl;
  scm_c_primitive_load(resname.c_str());
  std::cout << "### DONE: Loading Script: " << resname << std::endl;
}

GameWorld*
GameWorldBuilder::get_world()
{
  GameWorld* the_world = world;

  // remove our world handle, so that we don't delete world
  // in the destructor
  world = 0;

  return the_world;
}

/* EOF */
