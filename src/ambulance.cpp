//  $Id: ambulance.cpp,v 1.7 2003/06/03 14:11:22 grumbel Exp $
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

#include "view.hpp"
#include "resource_manager.hpp"
#include "ambulance.hpp"

Ambulance::Ambulance()
  : sur(resources->get_sprite("feuerkraft/ambulance"))
{

}

void
Ambulance::draw (View& view)
{
  view.get_sc().color().draw(sur, 0, 0);
}


/* EOF */
