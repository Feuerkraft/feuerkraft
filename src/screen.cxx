//  $Id: screen.cxx,v 1.6 2003/06/05 21:17:11 grumbel Exp $
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

#include "screen.hxx"

Screen::Screen ()
{
}

Screen::~Screen ()
{
}

void 
Screen::draw (CL_GraphicContext& gc)
{
  for (GuiObjIter i = gui_objs.begin (); i != gui_objs.end (); ++i)
    {
      (*i)->draw(gc);
    }
}

void 
Screen::update (float delta)
{
  for (GuiObjIter i = gui_objs.begin (); i != gui_objs.end (); ++i)
    {
      (*i)->update (delta);
    }
}

void 
Screen::add (GuiObj* obj)
{
  gui_objs.push_back (obj);
}

void 
Screen::remove (GuiObj* obj)
{
  for (GuiObjIter i = gui_objs.begin (); i != gui_objs.end (); ++i)
    {
      if (*i == obj)
        {
          gui_objs.erase(i);
          return;
        }
    }
}

/* EOF */
