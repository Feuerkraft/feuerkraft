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

#ifndef SHOCKWAVE_HH
#define SHOCKWAVE_HH

#include "vector2d.hpp"
#include "game_obj.hpp"
#include "resource_manager.hpp"

class Shockwave : public GameObj
{
private:
  FloatVector2d pos;
  CL_Sprite sprite;
  float progress;
public:
  Shockwave (FloatVector2d arg_pos);
  virtual ~Shockwave ();

  void draw (View& view);
  void update (float);
  float  get_z_pos () { return -1; }
};

#endif

/* EOF */
