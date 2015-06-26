// Feuerkraft - A Tank Battle Game
// Copyright (C) 2000 Ingo Ruhnke <grumbel@gmail.com>
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

#ifndef FEUERKRAFT_BACKGROUND_HH
#define FEUERKRAFT_BACKGROUND_HH

#include <ClanLib/Display/sprite.h>
#include <ClanLib/Display/surface.h>

#include "game_obj.hpp"

/** should be moved to groundmaps/.. and renamed to BaseGroundMap or
    something like that */
class Background
  : public GameObj
{
private:
  CL_Sprite sprite;
  float z_pos;

public:
  Background(const CL_Sprite& sprite, float z_pos);
  virtual ~Background () {}

  void draw (View& draw);
  void update (float delta) {}

  virtual float  get_z_pos () { return z_pos; }
};

#endif

/* EOF */
