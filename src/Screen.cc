//  $Id: Screen.cc,v 1.1 2001/05/01 21:12:03 grumbel Exp $
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

#include "Screen.hh"

Screen::Screen ()
{
}

Screen::~Screen ()
{
}

void 
Screen::draw ()
{
  for (GuiObjIter i = gui_objs.begin (); i != gui_objs.end (); ++i)
    {
      (*i)->draw ();
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
Screen::add (boost::shared_ptr<GuiObj> obj)
{
  gui_objs.push_back (obj);
}

/* EOF */
