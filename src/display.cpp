// Feuerkraft - A Tank Battle Game
// Copyright (C) 2026 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#include "display.hpp"
#include "feuerkraft_error.hpp"

SDL_Window*   Display::window_   = nullptr;
SDL_Renderer* Display::renderer_ = nullptr;

void
Display::init(SDL_Window* window, SDL_Renderer* renderer)
{
  window_   = window;
  renderer_ = renderer;
}

void
Display::deinit()
{
  // Window/renderer lifetime is owned by Feuerkraft
  window_   = nullptr;
  renderer_ = nullptr;
}

SDL_Window*
Display::get_window()
{
  return window_;
}

SDL_Renderer*
Display::get_renderer()
{
  return renderer_;
}

int
Display::get_width()
{
  int w = 0;
  if (window_)
    SDL_GetWindowSize(window_, &w, nullptr);
  return w;
}

int
Display::get_height()
{
  int h = 0;
  if (window_)
    SDL_GetWindowSize(window_, nullptr, &h);
  return h;
}

void
Display::clear(const Color& color)
{
  if (!renderer_)
    return;
  SDL_Color c = color.to_sdl();
  SDL_SetRenderDrawColor(renderer_, c.r, c.g, c.b, c.a);
  SDL_RenderClear(renderer_);
}

void
Display::flip()
{
  if (renderer_)
    SDL_RenderPresent(renderer_);
}

bool
Display::is_fullscreen()
{
  if (!window_)
    return false;
  return (SDL_GetWindowFlags(window_) & SDL_WINDOW_FULLSCREEN_DESKTOP) != 0;
}

void
Display::set_fullscreen(bool enable)
{
  if (!window_)
    return;
  SDL_SetWindowFullscreen(window_,
                          enable ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0);
}

/* EOF */
