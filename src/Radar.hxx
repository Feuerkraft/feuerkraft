//  $Id: Radar.hxx,v 1.2 2002/03/26 16:46:36 grumbel Exp $
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
#include <SphriteLib/sphritelibGL.h>
#include "boost/dummy_ptr.hpp"
#include "GameWorld.hxx"
#include "Vehicle.hxx"
#include "GuiObj.hxx"

extern CL_ResourceManager* resources;

class Building;

class Radar : public GuiObj
{
private:
  boost::dummy_ptr<GameWorld> world;
  boost::dummy_ptr<Vehicle> vehicle;
  
  CL_Surface background;

  /** Position of the radar on the screen */
  CL_Vector pos;

  float angle;

  SpriteProviderStorage storage;
  Sprite* radar_line;
  
public:
  Radar (const CL_Vector& arg_pos,  boost::dummy_ptr<GameWorld> w, boost::dummy_ptr<Vehicle> v);
  ~Radar ();

  void draw ();
  void update (float delta);

  /** Draw a blip to the radar, where 'pos' is in world coordinates
      and size is the size of the object (1: projectile, 2: vehicle,
      3: large vehicle, 4: building) */
  void draw_blip (const CL_Vector& pos, int size);

private:
  void draw_vehicle (boost::dummy_ptr<Vehicle> vehicle);
};

#endif

/* EOF */
