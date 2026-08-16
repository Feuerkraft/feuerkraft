// Feuerkraft - A Tank Battle Game
// Copyright (C) 2026 Ingo Ruhnke <grumbel@gmail.com>

#include <vector>
#include <iostream>
#include "game_controllers.hpp"

namespace {

std::vector<SDL_GameController*> controllers;

void ensure_opened()
{
  if (!controllers.empty())
    return;

  int n = SDL_NumJoysticks();
  controllers.resize(static_cast<size_t>(n), nullptr);
  for (int i = 0; i < n; ++i)
    {
      if (!SDL_IsGameController(i))
        {
          std::cout << "GameControllers: index " << i
                    << " is not a GameController, skipping" << std::endl;
          continue;
        }
      SDL_GameController* gc = SDL_GameControllerOpen(i);
      if (!gc)
        {
          std::cerr << "GameControllers: open " << i << " failed: "
                    << SDL_GetError() << std::endl;
          continue;
        }
      controllers[static_cast<size_t>(i)] = gc;
      std::cout << "GameControllers: opened [" << i << "] "
                << SDL_GameControllerName(gc) << std::endl;
    }
}

} // namespace

SDL_GameController*
GameControllers::get(int index)
{
  ensure_opened();
  if (index < 0 || index >= static_cast<int>(controllers.size()))
    return nullptr;
  return controllers[static_cast<size_t>(index)];
}

int
GameControllers::count()
{
  ensure_opened();
  return static_cast<int>(controllers.size());
}

void
GameControllers::clear()
{
  for (SDL_GameController* gc : controllers)
    if (gc)
      SDL_GameControllerClose(gc);
  controllers.clear();
}

/* EOF */
