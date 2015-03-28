//  $Id: player_view.cpp,v 1.4 2003/06/04 13:10:09 grumbel Exp $
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

#include "player.hpp"
#include "player_view.hpp"

PlayerViewUpdater::PlayerViewUpdater(Player* arg_player) :
  VehicleViewUpdater(arg_player->get_current_unit()),
  player(arg_player)
{
}

void
PlayerViewUpdater::update(float delta, ViewState& state)
{
  // FIXME: Polling considered evil, maybe CL_Signal will help
  set_unit(player->get_current_unit());

  VehicleViewUpdater::update(delta, state);
}

/* EOF */
