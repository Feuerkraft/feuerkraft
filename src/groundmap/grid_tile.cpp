//  $Id: grid_tile.cpp,v 1.7 2003/06/03 14:11:22 grumbel Exp $
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

#include <ClanLib/core.h>
#include "../view.hpp"
#include "grid_tile.hpp"
#include "../resource_manager.hpp"

GridTile::GridTile (std::string filename)
{  
  //std::cout << "Loading: " << filename << std::endl;
  sprite = resources->get_sprite (filename);
  //std::cout << "Done: Loading: " << filename << std::endl;
}

void
GridTile::draw(View& view, float x, float y)
{
  view.get_sc().color().draw(sprite, x, y);
}

/* EOF */
