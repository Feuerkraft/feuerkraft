//  $Id: View.hh,v 1.2 2001/02/25 19:48:17 grumbel Exp $
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

#ifndef VIEW_HH
#define VIEW_HH

#include "GameWorld.hh"

class GameWorld;

class View
{
protected:
  GameWorld* world;
  int x1, y1;
  int x2, y2;
  int x_offset, y_offset;

public:
  View (GameWorld* world, int x1, int y1, int x2, int y2,
	int x_offset = 0, int y_offset = 0);
  virtual ~View ();

  void draw ();
  void set_view (int x_pos, int y_pos);
  virtual void update ();
  int get_x_offset ();
  int get_y_offset ();
  int get_x1 ();
  int get_x2 ();
  int get_y1 ();
  int get_y2 ();
};

#endif

/* EOF */
