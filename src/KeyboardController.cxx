//  $Id: KeyboardController.cxx,v 1.4 2002/04/08 21:10:34 grumbel Exp $
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
#include <ClanLib/display2.h>
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

  key_down_slot = window->get_ic ()->sig_key_down (0).connect (this, &KeyboardController::input_down);
}  

void
KeyboardController::input_down (const CL_Key& key)
{
  std::cout << "got input: " << key.id << " " << key.type << std::endl;
  
  bool value;
  if (key.type == CL_Key::released)
    {
      std::cout << "Release" << std::endl;
      value = false;
    }
  else
    {
      std::cout << "Press" << std::endl;
      value = true;
    }

  switch (key.id)
    {
    case 65362: // up
      up_key = value;
      down_key = !value;
      break;
    case 65364: // down
      down_key = value;
      up_key = !value;
      break;
    case 65363: // left
      left_key = value;
      right_key = !value;
      break;
    case 65361: // right
      right_key = value;
      left_key = !value;
      break;
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
  
  if (left_key)
    controllable->turn_left (delta);
  else if (right_key)
    controllable->turn_right (delta);
        
  if (up_key)
    controllable->increase_velocity (delta);
  else if (down_key)
    controllable->decrease_velocity (delta);

  if (mine_key)
    controllable->drop_mine ();

  if (fire_key)
    controllable->start_fire ();
  else
    controllable->stop_fire ();
}

/* EOF */
