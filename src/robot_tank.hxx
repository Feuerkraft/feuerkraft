//  $Id: robot_tank.hxx,v 1.4 2003/06/03 14:11:22 grumbel Exp $
// 
//  Feuerkraft - A Tank Battle Game
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

#ifndef HEADER_ROBOT_TANK_HXX
#define HEADER_ROBOT_TANK_HXX

#include "vector2d.hxx"
#include "vehicle.hxx"

/** */
class RobotTank : public Vehicle
{
private:
  enum ThrottleState { T_ACCELERATE, T_BREAK, T_NEUTRAL, T_MAX };
  enum SteeringState { S_LEFT, S_RIGHT, S_NEUTRAL, S_MAX };
  ThrottleState throttle_state;
  SteeringState steering_state;
  float max_velocity;

  CL_Sprite sprite;
  
  float ai_count;

public:
  RobotTank(float x, float y, float orientation, float velocity);

  void update (float delta);
  void update_ai (float delta);

  void draw(View& view);
  void draw_energie(View& view);
  void draw_radar(Radar& radar);
  void draw_levelmap(LevelMap& view);
  bool is_colliding (FloatVector2d obj_pos) { return false; }
private:
  RobotTank (const RobotTank&);
  RobotTank& operator= (const RobotTank&);
};

#endif

/* EOF */
