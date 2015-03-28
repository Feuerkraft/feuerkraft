//  $Id: mine.hpp,v 1.10 2003/06/20 20:54:23 grumbel Exp $
//
//  Feuerkraft - A Tank Battle Game
//  Copyright (C) 2000 Ingo Ruhnke <grumbel@gmx.de>
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

#ifndef MINE_HH
#define MINE_HH

#include "game_obj.hpp"
#include "explosion.hpp"

class AList;

class Mine : public GameObj
{
private:
  FloatVector2d pos;
  float active;
  bool  detonated;

  CL_Sprite sur;
  CL_Sprite sur_active;
  CL_Sprite hole;
public:
  Mine(const AList& lst);
  virtual ~Mine() {}

  FloatVector2d get_pos () { return pos; }
  void update (float);
  void draw (View& view);
  void detonate ();
  bool is_active ();

  void on_collision(GameObj* obj);
};

#endif

/* EOF */
