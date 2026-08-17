// Feuerkraft - A Tank Battle Game
// Copyright (C) 2026 Ingo Ruhnke <grumbel@gmail.com>

#include <vector>
#include <iostream>
#include <SDL.h>
#include "game_controllers.hpp"
#include "../log.hpp"

namespace {

std::vector<SDL_GameController*> controllers;
bool mappings_ready = false;

void ensure_mappings()
{
  if (mappings_ready)
    return;
  mappings_ready = true;

  /* Built-in GO-Super (R36S / ArkOS) mapping when CFW did not inject
     SDL_GAMECONTROLLERCONFIG. GUID from PortMaster / ArkOS notes. */
  static const char* builtin[] = {
    "190000004b4800000011000000010000,GO-Super Gamepad,a:b0,b:b1,back:b12,dpdown:b9,dpleft:b10,dpright:b11,dpup:b8,guide:b16,leftshoulder:b4,leftstick:b14,lefttrigger:b6,leftx:a0,lefty:a1,rightshoulder:b5,rightstick:b15,righttrigger:b7,rightx:a2,righty:a3,start:b13,x:b3,y:b2,platform:Linux,",
    "030000004c050000c405000000010000,PS4 Controller,a:b1,b:b2,back:b8,dpdown:h0.4,dpleft:h0.8,dpright:h0.2,dpup:h0.1,guide:b12,leftshoulder:b4,leftstick:b10,lefttrigger:a3,leftx:a0,lefty:a1,rightshoulder:b5,rightstick:b11,righttrigger:a4,rightx:a2,righty:a5,start:b9,x:b0,y:b3,platform:Linux,",
    nullptr
  };
  for (int i = 0; builtin[i]; ++i)
    {
      if (SDL_GameControllerAddMapping(builtin[i]) < 0)
        fk_log_warn("GameController mapping add failed: %s", SDL_GetError());
      else
        fk_log("GameController mapping registered");
    }
}

void ensure_opened()
{
  if (!controllers.empty())
    return;

  ensure_mappings();

  int n = SDL_NumJoysticks();
  controllers.resize(static_cast<size_t>(n), nullptr);
  int opened = 0;
  for (int i = 0; i < n; ++i)
    {
      if (!SDL_IsGameController(i))
        {
          fk_log_warn("GameControllers: index %d is joystick-only (no mapping)", i);
          continue;
        }
      SDL_GameController* gc = SDL_GameControllerOpen(i);
      if (!gc)
        {
          fk_log_error("GameControllers: open %d failed: %s", i, SDL_GetError());
          continue;
        }
      controllers[static_cast<size_t>(i)] = gc;
      ++opened;
      fk_log("GameControllers: opened [%d] %s", i, SDL_GameControllerName(gc));
    }
  if (n > 0 && opened == 0)
    fk_log_warn("Joystick(s) present but none have a gamecontroller mapping");
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
