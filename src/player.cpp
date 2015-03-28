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

#include <assert.h>
#include "player.hpp"

Player::Player(Unit* arg_unit)
{
  soldier = arg_unit;
  set_current_unit(arg_unit);
}

Unit*
Player::get_soldier()
{
  return soldier;
}

void
Player::set_soldier(Unit* new_soldier)
{
  soldier = new_soldier;
  set_current_unit(soldier);
}

void
Player::set_current_unit(Unit* arg_unit)
{
  unit = arg_unit;
}

Unit*
Player::get_current_unit()
{
  assert(unit);
  return unit;
}

/* EOF */
