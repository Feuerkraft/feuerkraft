//  $Id: fuelstation.hxx,v 1.10 2003/06/22 18:34:52 grumbel Exp $
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

#ifndef FUELSTATION_HH
#define FUELSTATION_HH

#include <ClanLib/Display/sprite.h>

#include "../view.hxx"
#include "../alist.hxx"
#include "fuelstation_data.hxx"

class AList;

class Fuelstation
  : public Building
{
private:
  CL_Sprite fuelstation;
  FloatVector2d pos;

  /** The refueling variable keeps track if the fuelstation is
      currently refueling a vehicle, which triggers a blink-mark to
      indicate that to the user */
  bool refueling;
public:
  Fuelstation (const AList& lst);
  virtual ~Fuelstation ();

  void draw(View& view);
  void draw_radar(Radar& radar);

  void update (float delta);

  int get_map_width () { return 2; }
  int get_map_height () { return 2; }
};

#endif

/* EOF */
