//  $Id: grid_tile.cxx,v 1.1 2003/04/19 22:39:07 grumbel Exp $
//
//  Pingus - A free Lemmings clone
//  Copyright (C) 2000 Ingo Ruhnke <grumbel@gmx.de>
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

#include <ClanLib/core.h>
#include "../View.hxx"
#include "GridTile.hxx"
#include "../ResourceManager.hxx"

GridTile::GridTile (std::string filename)
  : sprite (resources->get_sprite (filename))
{  
}

void
GridTile::draw (View* view, float x, float y)
{
  view->draw(sprite, CL_Vector (x, y));
}

/* EOF */
