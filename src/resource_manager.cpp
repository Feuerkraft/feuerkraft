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

#include <fstream>
#include <iostream>
#include <sstream>
#include <regex>
#include "path_manager.hpp"
#include "resource_manager.hpp"

ResourceManager* resources = nullptr;

ResourceManager::ResourceManager()
{
  load_resource_file(path_manager.complete("feuerkraft.xml"));
  load_resource_file(path_manager.complete("tiles.xml"));
}

ResourceManager::~ResourceManager()
{
}

void
ResourceManager::load_resource_file(const std::string& filename)
{
  std::ifstream in(filename.c_str());
  if (!in)
    {
      std::cerr << "ResourceManager: could not open " << filename << std::endl;
      return;
    }

  std::ostringstream ss;
  ss << in.rdbuf();
  parse_section(ss.str(), "");
}

void
ResourceManager::parse_section(const std::string& content, const std::string& /*prefix*/)
{
  // Tokenise by walking with regexes for section open/close and sprite blocks.
  // Match <image ... file="..."> with any attribute order
  std::regex token_re(
    "<section\\s+name=\"([^\"]+)\"\\s*>|</section>|"
    "<sprite\\s+name=\"([^\"]+)\"\\s*>|</sprite>|"
    "<image\\b[^>]*\\bfile=\"([^\"]+)\"",
    std::regex::ECMAScript);

  std::vector<std::string> section_stack;
  std::string current_sprite;
  std::vector<std::string> current_files;
  bool in_sprite = false;

  auto sbegin = std::sregex_iterator(content.begin(), content.end(), token_re);
  auto send   = std::sregex_iterator();

  for (auto i = sbegin; i != send; ++i)
    {
      const std::smatch& m = *i;
      const std::string& full = m.str();

      if (full.compare(0, 8, "<section") == 0)
        {
          section_stack.push_back(m[1].str());
        }
      else if (full == "</section>")
        {
          if (!section_stack.empty())
            section_stack.pop_back();
        }
      else if (full.compare(0, 7, "<sprite") == 0)
        {
          in_sprite = true;
          current_sprite = m[2].str();
          current_files.clear();
        }
      else if (full == "</sprite>")
        {
          if (in_sprite && !current_files.empty())
            {
              std::string key;
              for (size_t s = 0; s < section_stack.size(); ++s)
                {
                  if (s) key += "/";
                  key += section_stack[s];
                }
              if (!key.empty()) key += "/";
              key += current_sprite;

              sprite_files[key] = current_files;
              // also register short name if not already taken
              if (sprite_files.find(current_sprite) == sprite_files.end())
                sprite_files[current_sprite] = current_files;
            }
          in_sprite = false;
          current_sprite.clear();
          current_files.clear();
        }
      else if (full.compare(0, 6, "<image") == 0)
        {
          if (in_sprite)
            current_files.push_back(m[3].str());
        }
    }

  std::cout << "ResourceManager: loaded " << sprite_files.size()
            << " sprite entries" << std::endl;
}

Sprite
ResourceManager::get_sprite(const std::string& location)
{
  auto it = sprite_files.find(location);
  if (it == sprite_files.end())
    {
      std::cerr << "ResourceManager: sprite not found: " << location << std::endl;
      return Sprite();
    }

  Sprite sprite;
  bool first = true;
  for (const auto& file : it->second)
    {
      std::string path = path_manager.complete(file);
      if (first)
        {
          sprite = Sprite(path);
          first = false;
        }
      else
        {
          sprite.add_frame(path);
        }
    }
  sprite.set_alignment(origin_center);
  return sprite;
}

/* EOF */
