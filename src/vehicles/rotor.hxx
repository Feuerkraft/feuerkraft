//  $Id$
// 
//  Feuerkraft - A Tank Battle Game
//  Copyright (C) 2003 Ingo Ruhnke <grumbel@gmx.de>
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

#ifndef HEADER_FEUERKRAFT_VEHICLES_ROTOR_HXX
#define HEADER_FEUERKRAFT_VEHICLES_ROTOR_HXX

#include <ClanLib/Display/sprite.h>

class View;

class RotorDescription
{
public:
  enum Direction { LEFT, RIGHT }; 

  std::string   slow_sprite;
  std::string   fast_sprite;
  FloatVector2d offset;
  RotorDescription::Direction direction;
};

/** */
class Rotor
{
private:
  RotorDescription::Direction direction;
  FloatVector2d offset;
  bool running;

  float orientation;
  float velocity;

  float acceleration;
  float max_velocity;

  CL_Sprite slow;
  CL_Sprite fast;
public:
  Rotor(const RotorDescription& desc);

  void draw(View& view, const FloatVector2d& pos, float orientation);
  void update(float delta);

  void start();
  void stop();

  float get_velocity() { return velocity; }
  bool  is_running() { return velocity >= max_velocity; }
};

#endif

/* EOF */
