//  $Id: soldier.hxx,v 1.11 2003/06/04 21:07:54 grumbel Exp $
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

#ifndef SOLDIER_HH
#define SOLDIER_HH

#include "unit.hxx"
#include "resource_manager.hxx"

class Soldier : public Unit
{
private:
  CL_Sprite sur;

  float last_orientation;

  // Controll variables
  float acceleration;
  float steering;
public:
  Soldier(const FloatVector2d& new_pos);
  ~Soldier();

  void update_controlls(const InputEventLst& events);

  float get_angle () { return 0.0; }
  void draw (View& view);
  void update (float);

  bool is_colliding(FloatVector2d);
  
  float get_physical_size () { return 1.0; }
};

#endif

/* EOF */
