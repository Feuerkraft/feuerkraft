//  $Id: sprite_tile.cpp,v 1.4 2003/05/19 19:00:56 grumbel Exp $
//
//  Feuerkraft
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

#ifndef SPRITETILE_CXX
#define SPRITETILE_CXX

#include <ClanLib/display.h>
#include "sprite_tile.hpp"
#include "../resource_manager.hpp"
#include "../view.hpp"

SpriteTile::SpriteTile (const SpriteTileData& data)
  : SpriteTileData (data),
    sprite (resources->get_sprite (sprite_location.c_str ()))
{
  sprite.set_alignment (origin_top_left);
}

void
SpriteTile::draw(View& view, float x, float y)
{
  view.get_sc().color().draw(sprite, x, y);
}

/** FIXME: 'float delta' should be replaced with GameDelta */
void
SpriteTile::update (float delta)
{
  sprite.update (delta);
}

#endif

/* EOF */
