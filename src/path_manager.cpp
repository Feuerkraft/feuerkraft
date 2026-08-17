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

#include <iostream>
#include <SDL.h>
#include "system.hpp"
#include "path_manager.hpp"

PathManager path_manager;

PathManager::PathManager ()
  : path_found (false)
{
}

PathManager::~PathManager ()
{
}

void
PathManager::add_path (const std::string& path)
{
  //std::cout << "PathManager: add_path: " << path << std::endl;
  path_list.push_back (path);
}

std::string
PathManager::complete (const std::string& relative_path)
{
  if (base_path.empty() || base_path == ".")
    {
      /* Android assets and "." roots: avoid "./foo" so AssetManager gets
         a clean relative path. */
      return relative_path;
    }
  if (!base_path.empty() && base_path.back() == '/')
    return base_path + relative_path;
  return base_path + "/" + relative_path;
}

bool
PathManager::find_path (const std::list<std::string>& file_list)
{
  for (PathIter i = path_list.begin (); !path_found && i != path_list.end (); ++i)
    {
      bool found_file = true;
      for (PathIter f = file_list.begin (); found_file && f != file_list.end (); ++f)
	{
	  if (!System::exist(*i + "/" + *f))
	    found_file = false;
	}
      if (found_file)
	{
	  path_found = true;
	  base_path = *i;

	  SDL_Log("[PathManager] Using base_path: %s", base_path.c_str());

	  return true;
	}
    }

  SDL_Log("[PathManager] No base path found");

  return false;
}

/** Search for a path which contains the file 'file' */
bool
PathManager::find_path (const std::string& file)
{
  for (PathIter i = path_list.begin (); !path_found && i != path_list.end (); ++i)
    {
      if (System::exist(*i + "/" + file))
	{
	  path_found = true;
	  base_path = *i;

	  SDL_Log("[PathManager] Using base_path: %s", base_path.c_str());

	  return true;
	}
    }

  SDL_Log("[PathManager] No base path found");

  return false;
}

void
PathManager::set_path (const std::string& path)
{
  base_path = path;
}

/* EOF */
