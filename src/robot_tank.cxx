//  $Id: robot_tank.cxx,v 1.6 2003/06/03 14:11:22 grumbel Exp $
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

#include "vector2d.hxx"
#include "view.hxx"
#include "math.hxx"
#include "resource_manager.hxx"
#include "robot_tank.hxx"

RobotTank::RobotTank(float x_, float y_, float orientation_, float velocity_)
{
  pos.x = x_;
  pos.y = y_;
  orientation = orientation_; 
  velocity = velocity_;

  max_velocity = 150.0f;
  throttle_state = T_NEUTRAL;
  steering_state = S_NEUTRAL;

  sprite = resources->get_sprite("feuerkraft/trooper");
  sprite.set_alignment(origin_center);

  ai_count = 0;
}

void
RobotTank::update (float delta)
{
  update_ai(delta);

  const float max_acceleration = 25.0f;
  const float max_deceleration = 10.0f;
  const float max_steering = 1.0f;

  // update velocity
  switch(throttle_state)
    {
    case T_ACCELERATE:
      velocity += max_acceleration * delta;
      break;
    case T_NEUTRAL:
      velocity -= 5.0f * delta;
      break;
    case T_BREAK:
      velocity -= max_deceleration * delta;
      break;
    default:
      assert(false);
    }

  if (velocity < 0)
    velocity = 0;
  else if (velocity > max_velocity)
    velocity = max_velocity;

  // update orientation
  switch(steering_state)
    {
    case S_LEFT:
      orientation += max_steering * delta;
      break;
    case S_NEUTRAL:
      // do nothing
      break;
    case S_RIGHT:
      orientation -= max_steering * delta;
      break;
    default:
      assert(false);
    }

  // update position
  FloatVector2d vec(velocity * delta, 0);
  vec.set_orientation(orientation);
  pos += vec;
}

void
RobotTank::update_ai (float delta)
{
  ai_count += delta;
  
  if (ai_count > 2)
    {
      ai_count = 0;
      
      switch (rand() % 5)
        {
        case 0:
        case 1:
        case 2:
          throttle_state = T_ACCELERATE;
          break;
        case 3:
          throttle_state = T_BREAK;
          break;
        case 4:
          throttle_state = T_NEUTRAL;
          break;
        }
      steering_state = SteeringState(rand() % S_MAX);
    }
}

void
RobotTank::draw (View& view)
{
  // FIXME: Orientation is wrong
  sprite.set_angle(Math::deg2rad(-orientation - Math::pi_2));
  view.get_dc().draw(sprite, pos.x, pos.y);
}

void
RobotTank::draw_energie (View& view)
{
}

void
RobotTank::draw_radar (Radar& radar)
{
}

void
RobotTank::draw_levelmap (LevelMap& view)
{
}

/* EOF */
