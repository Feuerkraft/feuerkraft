//  $Id: SpriteTile.cxx,v 1.2 2002/03/09 14:53:51 grumbel Exp $
// 
//  Feuerkraft
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

#ifndef SPRITETILE_CXX
#define SPRITETILE_CXX

#include <ClanLib/display.h>
#include <SphriteLib/sphritelibGL.h>
#include "SpriteTile.hxx"

extern CL_ResourceManager* resources;

SpriteTile::SpriteTile (const SpriteTileData& data)
  : SpriteTileData (data)
{
  SpriteProviderStorage storage;
  storage.add (new SpriteProvider (sprite_location.c_str (), resources));
  sprite = storage.create (sprite_location);
}

void
SpriteTile::draw (float x, float y)
{
  assert (sprite);
  sprite->draw ((int) x, (int) y);
  //std::cout << "draw: " << sprite_location << std::endl;
}

/** FIXME: 'float delta' should be replaced with GameDelta */
void
SpriteTile::update (float delta)
{
  assert (sprite);
  sprite->update (delta);
}

#endif

/* EOF */
