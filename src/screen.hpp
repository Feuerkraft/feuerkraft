//  $Id: screen.hpp,v 1.8 2003/06/06 09:49:00 grumbel Exp $
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

#ifndef SCREEN_HH
#define SCREEN_HH

#include <vector>
#include "gui_obj.hpp"

/** A screen is a collection of gui objects, it basically represents a
    complete screen. */
class Screen
  : public GuiObj
{
private:
  std::vector<GuiObj*> gui_objs;
  typedef std::vector<GuiObj*>::iterator GuiObjIter;
  
public:
  Screen ();
  virtual ~Screen ();

  virtual void draw (CL_GraphicContext& gc);
  virtual void update (float delta);
 
  bool has(GuiObj* obj);
 
  /** FIXME: Who takes controll over the allocated object? Currently nobody... -> MEMLEAK*/
  virtual void add (GuiObj* obj);
  virtual void remove (GuiObj* obj);
};

#endif

/* EOF */
