//  $Id: soldier.cxx,v 1.10 2003/06/04 14:46:10 grumbel Exp $
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

#include <iostream>
#include "view.hxx"
#include "soldier.hxx"

Soldier::Soldier(const FloatVector2d& arg_pos) 
  : sur (resources->get_sprite("feuerkraft/soldier"))
{
  pos = arg_pos;
}

Soldier::~Soldier ()
{
}

void
Soldier::update_controlls(const InputEventLst& events)
{
  for (InputEventLst::const_iterator i = events.begin(); i != events.end(); ++i)
    {
      switch (i->type)
        {
        case AXIS_EVENT:
          switch (i->axis.name)
            {
            case ACCELERATE_AXIS:
              //std::cout << "Accelerate: " << i->axis.pos << std::endl;
              acceleration = i->axis.pos;
              break;
            case ORIENTATION_AXIS:
              //std::cout << "Steering: " << i->axis.pos << std::endl;
              steering = i->axis.pos;
              break;
            default:
              std::cout << "Unknown axis: " << i->axis.name << std::endl;
            }
          break;
        default:
          std::cout << "Unknown event type: " << i->type << std::endl;
        }
    }
}

void 
Soldier::draw (View& view)
{
  view.draw (sur, pos);
}

void 
Soldier::update (float delta)
{
  FloatVector2d velocity;

  velocity.y = acceleration;
  velocity.x = steering;

  pos += velocity * 250.0f * delta;
}

bool 
Soldier::is_colliding(FloatVector2d obj_pos)
{
  FloatVector2d diff = obj_pos - pos;
  if (diff.get_length() > 5)
    return false;
  else
    return true;
}

/* EOF */
