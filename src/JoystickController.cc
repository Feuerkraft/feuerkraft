//  $Id: JoystickController.cc,v 1.4 2001/02/20 11:20:30 mbn Exp $
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

void 
JoystickController::update ()
{
  if (dir_axis && dir_axis->get_pos () > 0.5)
    controllable->turn_left ();
  else if (dir_axis && dir_axis->get_pos () < -0.5)
    controllable->turn_right ();
  
  if (left_t && left_t->is_pressed ())
    controllable->turn_left2 ();
  else if (right_t && right_t->is_pressed ())
    controllable->turn_right2 ();

  if (vel_axis && vel_axis->get_pos () < -0.5)
    controllable->increase_velocity ();
  else if (vel_axis && vel_axis->get_pos () > 0.5)
    controllable->decrease_velocity ();

  if (fire && fire->is_pressed ())
    controllable->start_fire ();
  else
    controllable->stop_fire ();    

  if (drop_mine && drop_mine->is_pressed ())
    controllable->drop_mine ();
}
  

/* EOF */
