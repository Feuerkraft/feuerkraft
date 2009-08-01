//  $Id: screen.cpp,v 1.7 2003/06/06 09:49:00 grumbel Exp $
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

#include "screen.hpp"

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

bool
Screen::has(GuiObj* obj)
{
  for (GuiObjIter i = gui_objs.begin (); i != gui_objs.end (); ++i)
    if (obj == *i)
      return true;
  
  return false;
}

void 
Screen::add (GuiObj* obj)
{
  if (!has(obj))
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
