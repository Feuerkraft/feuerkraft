//  $Id$
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

#ifndef HEADER_ROCKET_HXX
#define HEADER_ROCKET_HXX

#include "vector2d.hxx"
#include "game_obj.hxx"

/** */
class Rocket : public GameObj
{
private:
  CL_Sprite sprite;
  CL_Sprite smoke;
  FloatVector2d pos;
  float orientation;
  float velocity;
  float max_velocity;
  float life_time;
public:
  Rocket(const FloatVector2d& pos, float orientation);
  ~Rocket();

  void draw(View& view);
  void update(float delta);

  void detonate();
  void on_collision_with_building(Building* building);
private:
  Rocket (const Rocket&);
  Rocket& operator= (const Rocket&);
};

#endif

/* EOF */
