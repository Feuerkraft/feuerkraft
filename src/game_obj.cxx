//  $Id: game_obj.cxx,v 1.3 2003/05/11 11:20:44 grumbel Exp $
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

#include <iostream>
#include "property_set.hxx"
#include "game_obj.hxx"

GameObj::GameObj()
  : id(-1),
    remove_me (false) 
{
  properties = new PropertySet();
  properties->register_int("id", &id);
  properties->register_bool("remove-me", &remove_me);
}

GameObj::~GameObj()
{
  delete properties;
}

void
GameObj::on_collision(GameObj* obj)
{
  std::cout << "GameObj: collision from " << get_id() << " with: " << obj->get_id() << std::endl;
}

void
GameObj::on_collision_with_building(Building* building)
{
  std::cout << "GameObj: collision with building: " << get_id() << std::endl;
}

/* EOF */
