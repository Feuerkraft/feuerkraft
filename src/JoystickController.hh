//  $Id: JoystickController.hh,v 1.2 2001/02/18 00:49:16 grumbel Exp $
// 
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

#ifndef JOYSTICKCONTROLLER_HH
#define JOYSTICKCONTROLLER_HH

#include "Controller.hh"

class JoystickController : public Controller
{
private:
  CL_InputAxis* vel_axis;
  CL_InputAxis* dir_axis;
  
  CL_InputButton* left_t;
  CL_InputButton* right_t;
  CL_InputButton* fire;
  CL_InputButton* drop_mine;

public:
  JoystickController (Controllable* obj) : 
    Controller (obj)
  {
    if (CL_Input::joysticks.size () >= 1)
      {
	vel_axis = CL_Input::joysticks[0]->get_axis (1);
	dir_axis = CL_Input::joysticks[0]->get_axis (0);
    
	left_t = CL_Input::joysticks[0]->get_button (7);
	right_t = CL_Input::joysticks[0]->get_button (6);
	fire = CL_Input::joysticks[0]->get_button (4);
	drop_mine = CL_Input::joysticks[0]->get_button (1);
      }
  }

  virtual void update ();
};

#endif

/* EOF */
