//  $Id: soldier.hpp,v 1.16 2003/06/20 20:54:23 grumbel Exp $
// 
//  Feuerkraft - A Tank Battle Game
//  Copyright (C) 2000 Ingo Ruhnke <grumbel@gmx.de>
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//  
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//  
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.

#ifndef SOLDIER_HH
#define SOLDIER_HH

#include "soldier_ai.hpp"
#include "unit.hpp"
#include "resource_manager.hpp"

class AList;
class SoldierAI;

class Soldier : public Unit
{
private:
  SoldierAI* ai;
  CL_Sprite sur;
  CL_Sprite sur_light;

  // Controll variables
  float acceleration;
  float steering;
  
public:
  Soldier(const AList& lst);
  ~Soldier();

  void update_controlls(const Controller& events);

  float get_angle () { return 0.0; }
  void  draw (View& view);
  void  update (float);

  bool is_colliding(FloatVector2d);
  
  float get_physical_size () { return 1.0; }

  void attach_ai();

  void deattach_ai();

private:
  Soldier(const Soldier&);
  Soldier& operator=(const Soldier&);
};

#endif

/* EOF */
