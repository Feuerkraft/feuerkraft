//  $Id: player_view.cxx,v 1.1 2003/05/19 10:55:05 grumbel Exp $
//
//  Pingus - A free Lemmings clone
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

PlayerView::PlayerView(int x1, int y1, int x2, int y2, Player* arg_player)
  : VehicleView(x1, y1, x2, y2, arg_player->get_current_vehicle()),
    player(arg_player)
{
}

void
PlayerView::update(float delta)
{
  // FIXME: Polling considered evil, maybe CL_Signal will help
  VehicleView::set_vehicle(player->get_current_vehicle());
  VehicleView::update(delta);
}

/* EOF */
