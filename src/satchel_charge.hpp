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

#ifndef HEADER_SATCHEL_CHARGE_HXX
#define HEADER_SATCHEL_CHARGE_HXX

#include <ClanLib/Display/sprite.h>
#include "game_obj.hpp"

class AList;

/** A SatchelCharge is basically a remote controlled mine. FIXME:
    FIXME: Merging SatchelCharge and Mine into an own class might be a
    good idea */
class SatchelCharge : public GameObj
{
private:
  FloatVector2d pos;
  CL_Sprite sprite;
public:
  SatchelCharge(const AList& lst);

  void update (float);
  void draw (View& view);

  void detonate();
private:
  SatchelCharge (const SatchelCharge&);
  SatchelCharge& operator= (const SatchelCharge&);
};

#endif

/* EOF */
