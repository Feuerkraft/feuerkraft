//  $Id: joystick_controller.hxx,v 1.3 2003/05/03 16:21:35 grumbel Exp $
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

#include "controller.hxx"

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
  JoystickController (Controllable* obj);
  virtual void update (float delta);
};

#endif

/* EOF */
