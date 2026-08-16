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

#include <stdio.h>
#include <iostream>
#include <vector>
#include <SDL.h>
#include "display.hpp"
#include "screenshot.hpp"

void
Screenshot::write_screenshot_pnm(const std::string& filename)
{
  SDL_Renderer* renderer = Display::get_renderer();
  if (!renderer)
    return;

  int width  = Display::get_width();
  int height = Display::get_height();
  if (width <= 0 || height <= 0)
    return;

  std::vector<unsigned char> pixels(width * height * 4);
  if (SDL_RenderReadPixels(renderer, nullptr, SDL_PIXELFORMAT_RGB24,
                           pixels.data(), width * 3) != 0)
    {
      // Try with a temporary target - some drivers need a texture
      std::cerr << "Screenshot: RenderReadPixels failed: " << SDL_GetError() << std::endl;
      return;
    }

  FILE* out = fopen(filename.c_str(), "wb");
  if (!out)
    {
      perror(filename.c_str());
      return;
    }

  fprintf(out,
          "P6\n"
          "# CREATOR: Feuerkraft\n"
          "%d %d\n"
          "255\n",
          width, height);

  // RGB24 from top to bottom; original wrote bottom-up
  for (int y = height - 1; y >= 0; --y)
    fwrite(pixels.data() + y * width * 3, 1, width * 3, out);

  fclose(out);
}

/* EOF */
