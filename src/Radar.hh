//  $Id: Radar.hh,v 1.1 2001/05/01 10:44:54 grumbel Exp $
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

#ifndef RADAR_HH
#define RADAR_HH

#include <ClanLib/core.h>
#include <ClanLib/display.h>
#include "boost/dummy_ptr.hpp"
#include "GameWorld.hh"
#include "Vehicle.hh"
#include "GuiObj.hh"

extern CL_ResourceManager* resources;

class Radar : public GuiObj
{
private:
  boost::dummy_ptr<GameWorld> world;
  boost::dummy_ptr<Vehicle> vehicle;
  CL_Surface background;
  CL_Vector pos;
  float angle;
  
public:
  Radar (const CL_Vector& arg_pos,  boost::dummy_ptr<GameWorld> w, boost::dummy_ptr<Vehicle> v);
  ~Radar ();

  void draw ();
  void update (float delta);

private:
  void draw_vehicle (boost::dummy_ptr<Vehicle> vehicle);
};

#endif

/* EOF */
