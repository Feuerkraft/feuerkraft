//  $Id: menu_item.hpp,v 1.4 2003/06/18 13:03:13 grumbel Exp $
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

#ifndef HEADER_MENU_ITEM_HXX
#define HEADER_MENU_ITEM_HXX

#include <string>

class Menu;

class MenuItemFunctor
{
public:
  MenuItemFunctor() {}
  virtual ~MenuItemFunctor() {}
  
  virtual void call() {}
};

class MenuItemSubMenuFunctor : public MenuItemFunctor
{
private:
  Menu* submenu;
public:
  MenuItemSubMenuFunctor(Menu* arg_submenu);
  void call();
};

template<class Func>
class MenuItemGenericFunctor : public MenuItemFunctor
{
private:
  Func func;
public:
  MenuItemGenericFunctor(const Func& arg_func)
    : func(arg_func) {}

  void call() { func(); }
};

/** */
class MenuItem
{
private:
  std::string label;
  MenuItemFunctor* functor;
public:
  MenuItem(const std::string& arg_label, MenuItemFunctor* arg_functor);
  ~MenuItem();

  void draw(int x, int y);
  void draw_highlight(int x, int y);

  void call();
private:
  MenuItem (const MenuItem&);
  MenuItem& operator= (const MenuItem&);
};

#endif

/* EOF */
