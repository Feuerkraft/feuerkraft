// Feuerkraft - A Tank Battle Game
// Copyright (C) 2002 Ingo Ruhnke <grumbel@gmail.com>
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

#include <cstring>
#include <SDL.h>
#include "keys.hpp"

const char*
keyid2string(int id)
{
  const char* name = SDL_GetScancodeName(static_cast<SDL_Scancode>(id));
  if (name && name[0])
    return name;
  return "UNKNOWN";
}

int
string2keyid(const char* key)
{
  if (!key)
    return SDL_SCANCODE_UNKNOWN;

  // Accept both "KEY_A" style and plain "a" / "A"
  if (std::strncmp(key, "KEY_", 4) == 0)
    key += 4;

  SDL_Scancode sc = SDL_GetScancodeFromName(key);
  if (sc != SDL_SCANCODE_UNKNOWN)
    return static_cast<int>(sc);

  // Common aliases from the old ClanLib key names
  if (std::strcmp(key, "ESCAPE") == 0) return SDL_SCANCODE_ESCAPE;
  if (std::strcmp(key, "RETURN") == 0) return SDL_SCANCODE_RETURN;
  if (std::strcmp(key, "SPACE") == 0) return SDL_SCANCODE_SPACE;
  if (std::strcmp(key, "LEFT") == 0) return SDL_SCANCODE_LEFT;
  if (std::strcmp(key, "RIGHT") == 0) return SDL_SCANCODE_RIGHT;
  if (std::strcmp(key, "UP") == 0) return SDL_SCANCODE_UP;
  if (std::strcmp(key, "DOWN") == 0) return SDL_SCANCODE_DOWN;

  return SDL_SCANCODE_UNKNOWN;
}

/* EOF */
