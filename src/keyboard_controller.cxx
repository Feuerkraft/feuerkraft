//  $Id: keyboard_controller.cxx,v 1.1 2003/04/19 22:39:06 grumbel Exp $
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

#include <ClanLib/core.h>
#include <ClanLib/display.h>
#include "Tank.hxx"
#include "Turret.hxx"
#include "KeyboardController.hxx"

KeyboardController::KeyboardController (CL_DisplayWindow* window, Controllable* obj)
  : Controller (obj) 
{
  left_key = false;
  right_key = false;
  left2_key = false;
  right2_key = false;
  mine_key = false;
  fire_key = false;
  up_key = false;
  down_key = false;

  key_up_slot = window->get_ic()->get_keyboard().sig_key_up().connect (this, &KeyboardController::input_down);
  key_down_slot = window->get_ic()->get_keyboard().sig_key_down().connect (this, &KeyboardController::input_down);
}  

void
KeyboardController::input_down (const CL_InputEvent& key)
{
  if (key.type == CL_InputEvent::released)
    {
      switch (key.id)
        {
        case CL_KEY_UP: // up
          up_key   = false;
          break;
        case CL_KEY_DOWN: // down
          down_key = false;
          break;
        case CL_KEY_LEFT: // left
          left_key = false;
          break;
        case CL_KEY_RIGHT: // right
          right_key = false;
          break;
        case CL_KEY_SPACE:
          fire_key = false;
          break;
        case CL_KEY_M:
          mine_key = false;
          break;
        }
    }
  else
    {
      switch (key.id)
        {
        case CL_KEY_UP: // up
          up_key   = true;
          break;
        case CL_KEY_DOWN: // down
          down_key = true;
          break;
        case CL_KEY_LEFT: // left
          left_key = true;
          break;
        case CL_KEY_RIGHT: // right
          right_key = true;
          break;
        case CL_KEY_SPACE:
          fire_key = true;
          break;
        case CL_KEY_M:
          mine_key = true;
          break;
        }
    }
}

void
KeyboardController::update (float delta)
{
  delta = delta * 50.0f;

  if (left2_key)
    controllable->turn_left2 (delta);
  else if (right2_key)
    controllable->turn_right2 (delta);
  
  if (left_key && !right_key)
    controllable->turn_left (delta);
  else if (right_key && !left_key)
    controllable->turn_right (delta);
        
  if (up_key && !down_key)
    controllable->increase_velocity (delta);
  else if (down_key && !up_key)
    controllable->decrease_velocity (delta);

  if (mine_key)
    controllable->drop_mine ();

  if (fire_key)
    controllable->start_fire ();
  else
    controllable->stop_fire ();
}

/* EOF */
