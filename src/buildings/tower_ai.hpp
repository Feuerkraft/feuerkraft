//  $Id: tower_ai.hpp,v 1.1 2003/06/18 13:04:21 grumbel Exp $
//
//  Pingus - A free Lemmings clone
//  Copyright (C) 2002 Ingo Ruhnke <grumbel@gmx.de>
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

#ifndef HEADER_TOWER_AI_HXX
#define HEADER_TOWER_AI_HXX

#include "../input/controller.hpp"
#include "../ai.hpp"
#include "tower.hpp"

/** */
class TowerAI : public AI
{
private:
  Tower* tower;
  Controller controller;
  float ai_count;

public:
  TowerAI(Tower* arg_tower);
  GameObj* get_object();
  void update(float delta);

private:
  TowerAI(const TowerAI&);
  TowerAI& operator=(const TowerAI&);
};

#endif

/* EOF */
