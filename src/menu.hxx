//  $Id: menu.hxx,v 1.4 2003/06/07 16:16:08 grumbel Exp $
// 
//  Pingus - A free Lemmings clone
//  Copyright (C) 2002 Ingo Ruhnke <grumbel@gmx.de>
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

#ifndef HEADER_MENU_HXX
#define HEADER_MENU_HXX

#include <vector>
#include "input/input_event.hxx"
#include "gui_obj.hxx"

class MenuItem;

/** */
class Menu : public GuiObj
{
private:
  typedef std::vector<MenuItem*> MenuItems;
  MenuItems items;
  int current_item;
public:
  Menu();
  ~Menu();

  void draw (CL_GraphicContext& gc);
  void update(float delta);
  void add_item(MenuItem*);
  
  void next_item();
  void previous_item();

  /** Evaluate the current item */
  void call_current_item();

  /** Hide the current menu */
  void hide();

  /** */
  void process_events(const InputEventLst& );
private:
  Menu (const Menu&);
  Menu& operator= (const Menu&);
};

#endif

/* EOF */