// Feuerkraft - A Tank Battle Game
// Copyright (C) 2000 Ingo Ruhnke <grumbel@gmx.de>
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

#ifndef FUELSTATION_HH
#define FUELSTATION_HH

#include <ClanLib/Display/sprite.h>
#include "../view.hpp"
#include "building.hpp"

class Fuelstation
  : public Building
{
private:
  CL_Sprite fuelstation;
  FloatVector2d pos;

  /** The refueling variable keeps track if the fuelstation is
      currently refueling a vehicle, which triggers a blink-mark to
      indicate that to the user */
  bool refueling;
public:
  Fuelstation (const AList& lst);
  virtual ~Fuelstation ();

  void draw(View& view);
  void draw_radar(Radar& radar);

  void update (float delta);

  int get_map_width () { return 2; }
  int get_map_height () { return 2; }
};

#endif

/* EOF */
