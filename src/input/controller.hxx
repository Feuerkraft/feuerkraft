//  $Id: controller.hxx,v 1.3 2003/06/18 21:43:50 grumbel Exp $
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

#ifndef HEADER_CONTROLLER_HXX
#define HEADER_CONTROLLER_HXX

#include "input_event.hxx"

/** The Controller class presents the current state of the controller
    and the input events that occurred on the controller since the
    last update */
class Controller
{
public:
  float orientation_axis;
  float accelerate_axis;
  float strafe_axis;

  bool primary_fire_button;

  InputEventLst events;

public:
  Controller();

  float get_axis_state(AxisName name) const;
  bool  get_button_state(ButtonName name) const;

  void  set_axis_state(AxisName name, float pos);
  void  set_button_state(ButtonName name, bool down);

  InputEventLst get_events() const;
};

#endif

/* EOF */
