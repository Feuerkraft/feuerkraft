//  $Id: feuerkraft.hpp,v 1.8 2003/06/09 20:27:31 grumbel Exp $
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

#ifndef FEUERKRAFT_HH
#define FEUERKRAFT_HH

#include <ClanLib/application.h>

class CL_DisplayWindow;
class CommandLineArguments;

/**
   \mainpage %Feuerkraft Index Page
 
   \section intro Introduction
 
   This is the source code documentation for Feuerkraft, not all
   members and functions might be documented, but source code is
   included, so you might still figure out what a function should do
   and what it shouldn't.
 

   \section code Quick Overview

   A very quick overview about the source code, it works like this:

   - everything starts from FeuerkraftMain

   - FeuerkraftMain constructs the GameWorld and a View

   - FeuerkraftMain enters a while(true) loop and updates the
   GameWorld repeatatly and redraws the View as necessary

   - everything in GameWorld is a GameObj and has a id, by which it
   can be accessed

   - GameObj objects are grouped into two main subclasses, Building
   objects and Unit objects

   - a Building is a GameObj that is aligned to the tile grid and
   unmovable

   - a Unit is something moveable, which is not restricted by the
   tile grid and which the player can controll

   - other GameObj objects might included brushes and other stuff that
   is not controllable by the player, but that is not yet written

   FIXME: Just a 'test' introduction, to fill the empty index page,
   rewrite me with something usefull


   \section style Coding Style
   
   Coding style is mostly the default GNU Emacs one for C++, in
   addition to that namespaces have a indent level of 0.

   Pointer holding objects allocated with \c new and which need to get
   deleted by \c delete are named SomeObject*, while pointers which
   only hold references to objects managed and allocated elsewhere are
   named SomeObjectPtr. typedef for SomeObjectPtr should be in the
   some_object.hpp file.
*/

/** Command Line arguments in a parsed and easily accessible form,
    no need to touch \a argc or \a argv */
extern CommandLineArguments* args;

/** Feuerkraft is wrapper class around main(), which itself is part of
    clanApp. */
class Feuerkraft : public CL_ClanApplication
{
private:
  /** Pointer to the main display window of Feuerkraft. FIXME: Could
      probally be placed in a DisplayManager or something like that */
  CL_DisplayWindow*     window;

public:
  Feuerkraft();
  ~Feuerkraft();
  
  void init();
  void deinit();
  int  main(int argc, char** argv);

private:
  void key_down(const CL_InputEvent& event);
};

#endif

/* EOF */
