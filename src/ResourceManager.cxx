//  $Id: ResourceManager.cxx,v 1.1 2002/04/07 16:24:01 grumbel Exp $
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
#include <ClanLib/Display2/Providers/png_provider.h>
#include "ResourceManager.hxx"

ResourceManager* resources;

ResourceManager::ResourceManager ()
{
  resource_manager = new CL_ResourceManager ("data/feuerkraft.scr", false);
}

ResourceManager::~ResourceManager ()
{
}

CL_Surface
ResourceManager::get_surface (const std::string& location)
{
  CL_PixelBuffer* buffer = new CL_PNGProvider ("data/images/" + location + ".png");
  return CL_Surface (buffer, true);
}

CL_Sprite
ResourceManager::get_sprite (const std::string& location)
{
  std::cout << "ResourceManager::get_sprite: " << location << std::endl;
  CL_SpriteDescription desc;
  desc.add_frame (new CL_PNGProvider ("data/images/" + location + ".png"), true);
  
  CL_Sprite sprite (desc);
  sprite.set_translation_hotspot (origin_center);
  return sprite;
}

CL_Sprite*
ResourceManager::get_sprite_ptr (const std::string& location)
{
  std::cout << "ResourceManager::get_sprite_ptr: " << location << std::endl;
  return new CL_Sprite ("pcxsprite", resource_manager);
}

/* EOF */
