//  $Id: resource_manager.cxx,v 1.11 2003/06/05 21:17:11 grumbel Exp $
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

#include <iostream>
#include <ClanLib/Display/surface.h>
#include <ClanLib/Display/font.h>
#include <ClanLib/Core/Resources/resource_manager.h>
#include <ClanLib/Core/System/error.h>
#include <ClanLib/Core/System/cl_assert.h>

#include "path_manager.hxx"
#include "resource_manager.hxx"

ResourceManager* resources;

ResourceManager::ResourceManager ()
{
  resource_manager  = new CL_ResourceManager(path_manager.complete("feuerkraft.xml"), false);
}

ResourceManager::~ResourceManager ()
{
}

CL_Surface
ResourceManager::get_surface (const std::string& location)
{
  try {
    return CL_Surface (location, resource_manager);
  } catch(CL_Error& err) {
      std::cout << "ResourceManager: Error: " << err.message << std::endl;
    return CL_Surface();
  }
}

CL_Sprite
ResourceManager::get_sprite (const std::string& location)
{
  try {
    CL_Sprite sprite(location, resource_manager);
    sprite.set_alignment(origin_center);
    return sprite;
  } catch (CL_Error& err) {
    std::cout << "ResourceManager: Error: " << err.message << std::endl;
    return CL_Sprite ();
  }
}

CL_Font
ResourceManager::get_font(const std::string& location)
{
  try {
    CL_Font font(location, resource_manager);
    return font;
  } catch(CL_Error& err) {
    std::cout << "Couldn't load font: " << location << std::endl;
    std::cout << "CL_Error: " << err.message << std::endl;
    assert(false);
    return CL_Font();
  }
}

/* EOF */
