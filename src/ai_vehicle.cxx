//  $Id: ai_vehicle.cxx,v 1.6 2003/05/07 16:30:26 grumbel Exp $
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

#include <math.h>
#include "resource_manager.hxx"
#include "game_world.hxx"
#include "particles/smoke_particle.hxx"
#include "ai_vehicle.hxx"

AIVehicle::AIVehicle(boost::dummy_ptr<GameWorld>  w, const CL_Vector& arg_pos)
  : GameObj(w),
    pos(arg_pos),
    length(0.0f),
    line_segments(pos.x, pos.y, 0.0f)
{
  sprite = resources->get_sprite("feuerkraft/trooper");
  sprite.set_alignment(origin_center);

  current_order.type = AI_VO_NONE;
  
  velocity = 100.0f;
  orientation = 0.0f;
}

void
AIVehicle::update(float delta)
{
#if 0
  if (current_order.type == AI_VO_NONE)
    {
      if (!orders.empty())
        {
          current_order = orders.back();
          orders.pop_back();
        }
    }

  switch(current_order.type)
    {
    case AI_VO_DRIVETO:
      {
        float old_orientation = orientation;
        
        CL_Vector target_pos(current_order.drive_to.pos.x,
                             current_order.drive_to.pos.y);

        orientation = atan2(target_pos.y - pos.y,
                            target_pos.x - pos.x);

        float distance = (pos - target_pos).norm();

        pos.x -= velocity * delta * cos(orientation+PI);
        pos.y -= velocity * delta * sin(orientation+PI);

        if (distance < (pos - target_pos).norm())
          {
            orientation = old_orientation;
            pos = target_pos;
            next_order();
          }
        if (rand()% 15 == 1)
          world->add (new SmokeParticle (get_world (), pos));
      } 
      break;

    case AI_VO_WAIT:
      current_order.wait.seconds -= delta;
      if (current_order.wait.seconds < 0)
        next_order();
      break;

    default:
      break;
    }
#else
  if (current_order.type != AI_VO_NONE)
    {
      length += 100.0f * delta;
      pos = line_segments.get_pos(length);
      orientation = line_segments.get_orientation(length);

      if (line_segments.get_length() < length)
        current_order.type = AI_VO_NONE;
    }
#endif
}

void
AIVehicle::draw (View* view)
{
  view->draw(sprite, pos, orientation + PI);
  //line_segments.draw(view);
}

void
AIVehicle::add_order(AIVehicleOrder order)
{
  orders.push_front(order);
}

void
AIVehicle::wait(float seconds)
{
  AIVehicleOrder order;
  
  order.type = AI_VO_WAIT;

  order.wait.sequence_id = SequenceManager::current()->start_sequence();
  order.wait.seconds = seconds;
  
  add_order(order);
}

void
AIVehicle::next_order()
{
  switch(current_order.type)
    {
    case AI_VO_DRIVETO:
      SequenceManager::current()->end_sequence(current_order.drive_to.sequence_id);
      break;
    case AI_VO_WAIT:
      SequenceManager::current()->end_sequence(current_order.wait.sequence_id);
      break;
    default:
      break;
    }

  if (!orders.empty())
    {
      current_order = orders.back();
      orders.pop_back();
    }
  else
    {
      current_order.type = AI_VO_NONE;
    }
}

void
AIVehicle::clear_orders()
{
  orders.clear();
  current_order.type = AI_VO_NONE;
}

void
AIVehicle::drive_to(const CL_Vector& n_pos)
{
#if 0
  AIVehicleOrder order;

  order.type = AI_VO_DRIVETO;

  order.drive_to.sequence_id = SequenceManager::current()->start_sequence();
  order.drive_to.pos.x = n_pos.x;
  order.drive_to.pos.y = n_pos.y;
  
  add_order(order);
#else
  current_order.type = AI_VO_DRIVETO;
  line_segments.add_controll_point(n_pos.x, n_pos.y, 50.0f);
#endif
}

/* EOF */
