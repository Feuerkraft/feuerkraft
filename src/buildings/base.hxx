//  $Id: base.hxx,v 1.8 2003/05/19 19:00:56 grumbel Exp $
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

#ifndef BASE_HH
#define BASE_HH

#include <ClanLib/Display/sprite.h>

#include "../view.hxx"
#include "building.hxx"
#include "base_data.hxx"

class Base : public Building
{
private:
  CL_Sprite sprite;
  FloatVector2d pos;

public:
  Base (const BaseData& data);
  virtual ~Base ();

  void draw (View& v);
  void draw_radar (Radar& radar);

  void update (float delta);

  int get_map_width ()  { return 0; }
  int get_map_height () { return 0; }
};

#endif

/* EOF */
