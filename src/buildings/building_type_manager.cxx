//  $Id: building_type_manager.cxx,v 1.1 2003/05/08 23:02:10 grumbel Exp $
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
#include "building_type_manager.hxx"

BuildingTypeManager* BuildingTypeManager::current_ = 0;

BuildingTypeManager::BuildingTypeManager()
{
  next_id = 2;
  current_ = this;
}

int
BuildingTypeManager::register_factory(BuildingFactory* factory)
{
  factories.push_back(factory);
  factory->id = next_id;
  return next_id++;
}

Building*
BuildingTypeManager::create_building(int type_id, const AList& params)
{
  for (Factories::iterator i = factories.begin(); i != factories.end(); ++i)
    {
      if ((*i)->id == type_id)
        {
          return (*i)->create(params);
        }
    }

  std::cout << "BuildingTypeManager: Invalid type handle: " << type_id << std::endl;
  return 0;
}

/* EOF */
