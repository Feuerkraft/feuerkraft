//  $Id: menu.hpp,v 1.5 2003/10/31 23:24:41 grumbel Exp $
// 
//  Pingus - A free Lemmings clone
//  Copyright (C) 2002 Ingo Ruhnke <grumbel@gmx.de>
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

#ifndef HEADER_MENU_HXX
#define HEADER_MENU_HXX

#include <vector>
#include "input/input_event.hpp"
#include "gui_obj.hpp"

class MenuItem;

/** */
class Menu : public GuiObj
{
private:
  typedef std::vector<MenuItem*> MenuItems;
  MenuItems items;
  int current_item;
  float pos;
  bool moving;
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
