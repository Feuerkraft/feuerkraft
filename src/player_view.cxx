//  $Id: player_view.cxx,v 1.3 2003/06/03 14:11:22 grumbel Exp $
//
//  Feuerkraft - A Tank Battle Game
//  Copyright (C) 2002 Ingo Ruhnke <grumbel@gmx.de>
//
//  This program is free software; you can redistribute it and/or
//  modify it under the terms of the GNU General Public License
//  as published by the Free Software Foundation; either version 2
//  of the License, or (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program; if not, write to the Free Software
//  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

#include "player.hxx"
#include "player_view.hxx"

PlayerViewUpdater::PlayerViewUpdater(Player* arg_player)
  : VehicleViewUpdater(arg_player->get_current_vehicle()),
    player(arg_player)
{
}

void
PlayerViewUpdater::update(float delta, ViewState& state)
{
  // FIXME: Polling considered evil, maybe CL_Signal will help
  set_vehicle(player->get_current_vehicle());

  VehicleViewUpdater::update(delta, state);
}

/* EOF */
