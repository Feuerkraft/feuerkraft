//  $Id: JoystickController.cc,v 1.8 2001/11/28 17:17:27 grumbel Exp $
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

#include "Tank.hh"
#include "Turret.hh"
#include "JoystickController.hh"

JoystickController::JoystickController (Controllable* obj) :
  Controller (obj),
  vel_axis(NULL),
  dir_axis(NULL),
  left_t(NULL),
  right_t(NULL),
  fire(NULL),
  drop_mine(NULL)
{
  if (CL_Input::joysticks.size () >= 1)
    {
      std::cout << "Joystick found" << std::endl;
      vel_axis = CL_Input::joysticks[0]->get_axis (1);
      dir_axis = CL_Input::joysticks[0]->get_axis (0);
    
      left_t = CL_Input::joysticks[0]->get_button (7);
      right_t = CL_Input::joysticks[0]->get_button (6);
      fire = CL_Input::joysticks[0]->get_button (4);
      drop_mine = CL_Input::joysticks[0]->get_button (1);
    }
  else
    {
      std::cout << "Joystick not found: " << CL_Input::joysticks.size () << std::endl;
    }
}

void 
JoystickController::update (float delta)
{
  if (CL_Input::joysticks.size () >= 1)
    {
      
      if (dir_axis && dir_axis->get_pos () > 0.5)
	controllable->turn_left (delta);
      else if (dir_axis && dir_axis->get_pos () < -0.5)
	controllable->turn_right (delta);
  
      if (left_t && left_t->is_pressed ())
	controllable->turn_left2 (delta);
      else if (right_t && right_t->is_pressed ())
	controllable->turn_right2 (delta);

      if (vel_axis && vel_axis->get_pos () < -0.5)
	controllable->increase_velocity (delta);
      else if (vel_axis && vel_axis->get_pos () > 0.5)
	controllable->decrease_velocity (delta);

      if (fire && fire->is_pressed ())
	controllable->start_fire ();
      else
	{
	  controllable->stop_fire ();    
	}

      if (drop_mine && drop_mine->is_pressed ())
	controllable->drop_mine ();
    }
}
  

/* EOF */
