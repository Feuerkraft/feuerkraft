//  $Id: soldier_ai.hxx,v 1.2 2003/06/18 14:38:28 grumbel Exp $
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

#ifndef HEADER_SOLDIER_AI_HXX
#define HEADER_SOLDIER_AI_HXX

#include "vector2d.hxx"
#include "input/controller.hxx"
#include "ai.hxx"

class Soldier;

/** */
class SoldierAI : public AI
{
private:
  Soldier* soldier;
  Controller controller;

  enum State { WAITING, GOTO_TARGET, RANDOM } state;

  FloatVector2d target_pos;
public:
  SoldierAI(Soldier* arg_soldier);
  GameObj* get_object();

  void update(float delta);

  void goto_to(const FloatVector2d& target_pos);
  void stop();
};

#endif

/* EOF */
