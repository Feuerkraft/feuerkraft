//  $Id: ai_vehicle.cxx,v 1.1 2003/04/28 21:20:37 grumbel Exp $
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
#include "ai_vehicle.hxx"

AIVehicle::AIVehicle(boost::dummy_ptr<GameWorld>  w, const CL_Vector& arg_pos)
  : GameObj(w),
    pos(arg_pos)
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
            std::cout << "Target Reached" << std::endl;
            orientation = old_orientation;
            pos = target_pos;
            next_order();
          }
      } 
      break;

    default:
      break;
    }
}

void
AIVehicle::draw (View* view)
{
  view->draw(sprite, pos, orientation + PI);
}

void
AIVehicle::add_order(AIVehicleOrder order)
{
  orders.push_front(order);
}

void
AIVehicle::next_order()
{
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
  AIVehicleOrder order;

  order.type = AI_VO_DRIVETO;

  order.drive_to.pos.x = n_pos.x;
  order.drive_to.pos.y = n_pos.y;
  
  add_order(order);
}

/* EOF */
