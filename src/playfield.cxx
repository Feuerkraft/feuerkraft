//  $Id: playfield.cxx,v 1.7 2003/06/09 20:27:31 grumbel Exp $
//
//  Feuerkraft - A Tank Battle Game
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

#include <ClanLib/Display/graphic_context.h>
#include "view.hxx"
#include "playfield.hxx"

Playfield::Playfield (int x1, int y1, int x2, int y2)
{
  view = new View(x1, y1, x2, y2);
}

Playfield::~Playfield ();

void
Playfield::draw(CL_GraphicContext& gc)
{
  gc.push_cliprect(CL_Rect(view->get_x1(),
                           view->get_y1(),
                           view->get_x2(),
                           view->get_y2()));
  view->draw();
  gc.pop_cliprect();
}

void
Playfield::update(float delta)
{
  view->update(delta)
}

/* EOF */
