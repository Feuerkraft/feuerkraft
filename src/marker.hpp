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

#ifndef HEADER_MARKER_HXX
#define HEADER_MARKER_HXX

#include <ClanLib/Display/sprite.h>
#include "game_obj.hpp"
#include "vector2d.hpp"

class AList;
class View;

/** A marker is a special guide for the player that gives visual
    informations on the radar and on the map. */
class Marker : public GameObj
{
private:
  CL_Sprite sprite;
  FloatVector2d pos;
  float passed_time;
public:
  Marker(const AList& lst);
  ~Marker();

  void draw  (View& view);
  void draw_radar(Radar& radar);
  void update(float delta);

  float get_z_pos() { return 10000; }
private:
  Marker (const Marker&);
  Marker& operator= (const Marker&);
};

#endif

/* EOF */
