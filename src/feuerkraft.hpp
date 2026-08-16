// Feuerkraft - A Tank Battle Game
// Copyright (C) 2000 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#ifndef FEUERKRAFT_HH
#define FEUERKRAFT_HH

#include <SDL.h>

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

   - everything starts from Feuerkraft::main

   - Feuerkraft constructs the GameWorld and a View

   - Feuerkraft enters a while(true) loop and updates the
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

/** Feuerkraft is the main application class. */
class Feuerkraft
{
private:
  /** Pointer to the main display window of Feuerkraft. */
  SDL_Window* window;

public:
  Feuerkraft();
  ~Feuerkraft();

  void init();
  void deinit();
  int  main(int argc, char** argv);

private:
  // Temporary: will be replaced by SDL event handling
  // void key_down(...);

private:
  Feuerkraft(const Feuerkraft&);
  Feuerkraft& operator=(const Feuerkraft&);
};

#endif

/* EOF */
