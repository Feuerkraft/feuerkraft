//  $Id: stone.cxx,v 1.2 2003/04/19 23:17:52 grumbel Exp $
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
#include "stone.hxx"

Stone::Stone (boost::dummy_ptr<GameWorld> w, const CL_Vector& arg_pos)
  : GameObj (w),
    sur (resources->get_sprite("feuerkraft/stone")),
    pos (arg_pos)
{
}

Stone::~Stone ()
{
}

void 
Stone::draw (View* view)
{
  view->draw (sur, pos);
}

void 
Stone::update (float delta)
{
}

/* EOF */