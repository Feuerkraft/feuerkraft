//  $Id: ResourceManager.cxx,v 1.4 2002/07/21 19:32:31 grumbel Exp $
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

#include <iostream>
//#include <ClanLib/Display2/Providers/png_provider.h>
#include "ResourceManager.hxx"

ResourceManager* resources;

ResourceManager::ResourceManager ()
{
  resource_manager = new CL_ResourceManager ("data/feuerkraft.scr", false);
  resource_manager2 = new CL_ResourceManager ("data/tiles.scr", false);
}

ResourceManager::~ResourceManager ()
{
}

CL_Surface
ResourceManager::get_surface (const std::string& location)
{
  return CL_Surface (location, resource_manager);
}

CL_Sprite
ResourceManager::get_sprite (const std::string& location)
{
  std::cout << "Loading: " << location << std::endl;
  try {
    return CL_Sprite (location, resource_manager);
  } catch (CL_Error& err) {
    std::cout << "Catch and Retry: " << err.message << std::endl;
    try {
      return CL_Sprite (location, resource_manager2);
    } catch (CL_Error& err) {
      std::cout << "Bailout: " << err.message << std::endl;
      cl_assert (0);
      return CL_Sprite ();
    }
  }
}

CL_Sprite*
ResourceManager::get_sprite_ptr (const std::string& location)
{
  std::cout << "ResourceManager::get_sprite_ptr: " << location << std::endl;
  return new CL_Sprite (get_sprite (location));
}

/* EOF */
