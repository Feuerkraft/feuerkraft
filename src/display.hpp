// Feuerkraft - A Tank Battle Game
// Copyright (C) 2026 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#ifndef HEADER_DISPLAY_HXX
#define HEADER_DISPLAY_HXX

#include <SDL.h>
#include "color.hpp"
#include "display/math_types.hpp"

/**
 * Thin facade around the SDL window/renderer.
 * Replaces the old CL_Display / CL_DisplayWindow surface.
 */
class Display
{
public:
  static void init(SDL_Window* window, SDL_Renderer* renderer);
  static void deinit();

  static SDL_Window*   get_window();
  static SDL_Renderer* get_renderer();

  static int  get_width();
  static int  get_height();

  static void clear(const Color& color = Color(0, 0, 0));
  static void flip();

  static bool is_fullscreen();
  static void set_fullscreen(bool enable);

  static void fill_rect(int x1, int y1, int x2, int y2, const Color& color);
  static void fill_rect(const Rect& r, const Color& color);
  static void draw_line(int x1, int y1, int x2, int y2, const Color& color);
  static void draw_rect(int x1, int y1, int x2, int y2, const Color& color);

private:
  static SDL_Window*   window_;
  static SDL_Renderer* renderer_;
};

#endif

/* EOF */
