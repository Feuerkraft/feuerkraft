//  $Id: Fuelstation.cc,v 1.1 2001/05/05 09:04:58 grumbel Exp $
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

#include "Fuelstation.hh"

extern CL_ResourceManager* resources;

Fuelstation::Fuelstation (boost::dummy_ptr<GameWorld> world, CL_Vector arg_pos)
  : GameObj (world),
    fuelstation ("feuerkraft/fuelstation", resources),
    pos (arg_pos)
{
}

Fuelstation::~Fuelstation ()
{
}

void 
Fuelstation::draw (View* view)
{
  view->draw (fuelstation, 
	      pos.x - fuelstation.get_width ()/2, 
	      pos.y - fuelstation.get_height ()/2);
}

void 
Fuelstation::update (float delta)
{
}

/* EOF */
