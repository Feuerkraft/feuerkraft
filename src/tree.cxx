//  $Id: tree.cxx,v 1.2 2003/04/19 23:17:52 grumbel Exp $
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

#include "resource_manager.hxx"
#include "tree.hxx"

Tree::Tree (boost::dummy_ptr<GameWorld>  w, const TreeData& arg_data)
  : GameObj (w),
    data (arg_data),
    sur (resources->get_sprite(data.name.c_str ())),
    sur_shadow (resources->get_sprite((data.name + "_shadow").c_str ()))
{
}

Tree::~Tree ()
{
}
  
void 
Tree::draw (View* view)
{
  view->draw (sur_shadow, int(data.pos.x - 15), int(data.pos.y - 15));
  view->draw (sur, data.pos);
}

GameObjData* 
Tree::get_data ()
{
  return &data; 
}

/* EOF */
