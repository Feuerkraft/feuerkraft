//  $Id: JoystickController.cc,v 1.1 2001/02/17 20:02:11 grumbel Exp $
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
  if (dir_axis->get_pos () > 0.5)
    controllable->turn_left ();
  else if (dir_axis->get_pos () < -0.5)
    controllable->turn_right ();
  
  if (left_t->is_pressed ())
    dynamic_cast<Tank*>(controllable)->get_turret ()->increase_angle ();
  else if (right_t->is_pressed ())
    dynamic_cast<Tank*>(controllable)->get_turret ()->decrease_angle ();

  if (vel_axis->get_pos () < -0.5)
    controllable->increase_velocity ();
  else if (vel_axis->get_pos () > 0.5)
    controllable->decrease_velocity ();

  if (fire->is_pressed ())
    controllable->start_fire ();
  else
    controllable->stop_fire ();    
}
  

/* EOF */
