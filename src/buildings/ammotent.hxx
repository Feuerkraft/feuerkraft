//  $Id: ammotent.hxx,v 1.6 2003/05/18 09:38:44 grumbel Exp $
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

#ifndef AMMOTENT_HH
#define AMMOTENT_HH

#include <ClanLib/Display/sprite.h>

#include "../view.hxx"
#include "building.hxx"
#include "ammotent_data.hxx"

class Ammotent : public Building
{
private:
  CL_Sprite ammotent;
  CL_Vector pos;
  bool reloading;
  
public:
  Ammotent (const AmmotentData&);
  virtual ~Ammotent ();

  void draw (ViewPtr view);
  void draw_radar (RadarPtr radar);

  void update (float delta);  

  int get_map_width () { return 2; }
  int get_map_height () { return 2; }
};

#endif

/* EOF */
