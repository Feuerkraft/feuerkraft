//  $Id: custom_building.hxx,v 1.4 2003/05/19 19:00:56 grumbel Exp $
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

#ifndef HEADER_CUSTOM_BUILDING_HXX
#define HEADER_CUSTOM_BUILDING_HXX

#include <ClanLib/Display/sprite.h>
#include "../energie.hxx"
#include "building.hxx"

class AList;

/** The CustomBuilding is a special kind of building that is
    customizable in a number of ways, its surface, size, covered
    region, energie, armor and other stuff can be customized via
    parameters. It is mainly there to allow users to create there own
    building types from Scheme */
class CustomBuilding : public Building
{
private:
  CL_Sprite sprite;
  Energie energie;
  // FIXME: Position handling here is ugly
  int x_pos;
  int y_pos;

  int width;
  int height;
public:
  CustomBuilding(const AList& type, const AList& lst);
  virtual ~CustomBuilding() {}

  int get_x_pos () { return x_pos; }
  int get_y_pos () { return y_pos; }

  void draw(View&);
  void draw_energie(View& view);

  void update(float);

  int  get_map_width() { return width; }
  int  get_map_height() { return height; }

  void collide (Projectile*);
private:
  CustomBuilding (const CustomBuilding&);
  CustomBuilding& operator= (const CustomBuilding&);
};

#endif

/* EOF */
