//  $Id: tree.cxx,v 1.9 2003/05/19 19:00:56 grumbel Exp $
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

#include <iostream>
#include "view.hxx"
#include "property_set.hxx"
#include "resource_manager.hxx"
#include "tree.hxx"

Tree::Tree()
{
  properties->register_string("sprite", &sprite_name);
  properties->register_float("x-pos", &pos.x);
  properties->register_float("y-pos", &pos.y);
  properties->register_float("z-pos", &z_pos);
  z_pos = 10.0f;
}

Tree::~Tree ()
{
}

void
Tree::properties_updated()
{
  std::cout << "Loading Tree Sprites" << std::endl;
  sur = resources->get_sprite(sprite_name);
  
  sur.set_alignment(origin_center);
}
  
void 
Tree::draw (View& view)
{
  view.draw(sur, pos);
}

/* EOF */
