//  $Id: ResourceManager.hxx,v 1.3 2002/07/21 19:32:31 grumbel Exp $
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

#ifndef RESOURCEMANAGER_HXX
#define RESOURCEMANAGER_HXX

#include <string>
#include <ClanLib/core.h>
#include <ClanLib/display.h>

/** lalala... ugly */
class ResourceManager
{
private:
  CL_ResourceManager* resource_manager;
  CL_ResourceManager* resource_manager2;

public:
  ResourceManager ();
  ~ResourceManager ();

  /** Load a CL_Sprite */
  CL_Surface get_surface (const std::string& location);
  CL_Sprite get_sprite (const std::string& location);
  CL_Sprite* get_sprite_ptr (const std::string& location);
};

//extern CL_SpriteProviderStorage* storage;
extern ResourceManager* resources;

#endif

/* EOF */
