//  $Id: display_manager.hxx,v 1.2 2003/06/06 11:11:19 grumbel Exp $
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

#ifndef HEADER_DISPLAY_MANAGER_HXX
#define HEADER_DISPLAY_MANAGER_HXX

#include "screen.hxx"

class GuiObj;
class Menu;
class Radar;
class Help;
class LevelMap;
class VehicleStatus;
class MessageBuffer;

/** The DisplayManager manages all screen components, radar, levelmap,
    menu playfield and other things. There is currently only one,
    later it might need to be split up for multiplayer. */
class DisplayManager
{
  // Static Part
private:
  static DisplayManager* current_;
public:
  static DisplayManager* current() { return current_; }; 
  static void init();
  static void deinit();

  // Object Part
private:
  Screen  screen;

  Help*          help;
  LevelMap*      level_map;
  Radar*         radar;
  VehicleStatus* vehicle_status;
  MessageBuffer* message_buffer;
  Menu*          menu;
public:
  DisplayManager();
  ~DisplayManager();

  void add(GuiObj*);
  void update(float delta);
  void draw(CL_GraphicContext& gc);

  void show_levelmap();
  void hide_levelmap();

  void show_help();
  void hide_help();
  
  /** Show the given menu */
  void show_menu(Menu* menu);
  
  /** Hide the current menu */
  void hide_menu();

  /** @retun the currently shown menu or 0 if none is shown */
  Menu* get_menu() const { return menu; }
private:
  DisplayManager (const DisplayManager&);
  DisplayManager& operator= (const DisplayManager&);
};

#endif

/* EOF */
