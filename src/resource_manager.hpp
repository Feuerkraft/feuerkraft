// Feuerkraft - A Tank Battle Game
// Copyright (C) 2000 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#ifndef RESOURCEMANAGER_HXX
#define RESOURCEMANAGER_HXX

#include <string>
#include <map>
#include <vector>
#include "sprite.hpp"

/** Loads sprites (and later fonts) from the data directory.
 *  Understands the subset of the old ClanLib resource XML used by
 *  Feuerkraft (sprite + image file entries, nested sections). */
class ResourceManager
{
private:
  /** Maps "section/name" or "name" to a list of image file paths */
  std::map<std::string, std::vector<std::string> > sprite_files;

  void load_resource_file(const std::string& filename);
  void parse_section(const std::string& content, const std::string& prefix);

public:
  ResourceManager();
  ~ResourceManager();

  Sprite get_sprite(const std::string& location);
  // Surface API kept as alias for now
  Sprite get_surface(const std::string& location) { return get_sprite(location); }

private:
  ResourceManager(const ResourceManager&);
  ResourceManager& operator=(const ResourceManager&);
};

extern ResourceManager* resources;

#endif

/* EOF */
