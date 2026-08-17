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

#include <iostream>
#include "scene_context.hpp"
#include "display.hpp"

class SceneContextImpl
{
public:
  DrawingContext color;
  DrawingContext light;
  DrawingContext highlight;

  SDL_Texture* color_tex;
  SDL_Texture* light_tex;
  SDL_Texture* highlight_tex;
  int tex_w;
  int tex_h;

  SceneContextImpl()
    : color_tex(nullptr), light_tex(nullptr), highlight_tex(nullptr),
      tex_w(0), tex_h(0)
  {
  }

  ~SceneContextImpl()
  {
    if (color_tex) SDL_DestroyTexture(color_tex);
    if (light_tex) SDL_DestroyTexture(light_tex);
    if (highlight_tex) SDL_DestroyTexture(highlight_tex);
  }

  void ensure_targets(SDL_Renderer* renderer, int w, int h)
  {
    if (color_tex && tex_w == w && tex_h == h)
      return;

    if (color_tex) { SDL_DestroyTexture(color_tex); color_tex = nullptr; }
    if (light_tex) { SDL_DestroyTexture(light_tex); light_tex = nullptr; }
    if (highlight_tex) { SDL_DestroyTexture(highlight_tex); highlight_tex = nullptr; }

    tex_w = w;
    tex_h = h;

    color_tex = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,
                                  SDL_TEXTUREACCESS_TARGET, w, h);
    light_tex = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,
                                  SDL_TEXTUREACCESS_TARGET, w, h);
    highlight_tex = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,
                                      SDL_TEXTUREACCESS_TARGET, w, h);

    if (!color_tex || !light_tex || !highlight_tex)
      {
        std::cerr << "SceneContext: failed to create render targets: "
                  << SDL_GetError() << std::endl;
      }

    if (color_tex)
      {
        SDL_SetTextureBlendMode(color_tex, SDL_BLENDMODE_BLEND);
        #if SDL_VERSION_ATLEAST(2, 0, 12)
        SDL_SetTextureScaleMode(color_tex, SDL_ScaleModeLinear);
        #endif
      }
    if (light_tex)
      {
        SDL_SetTextureBlendMode(light_tex, SDL_BLENDMODE_MOD); // multiply
        #if SDL_VERSION_ATLEAST(2, 0, 12)
        SDL_SetTextureScaleMode(light_tex, SDL_ScaleModeLinear);
        #endif
      }
    if (highlight_tex)
      {
        SDL_SetTextureBlendMode(highlight_tex, SDL_BLENDMODE_ADD);
        #if SDL_VERSION_ATLEAST(2, 0, 12)
        SDL_SetTextureScaleMode(highlight_tex, SDL_ScaleModeLinear);
        #endif
      }
  }
};

SceneContext::SceneContext()
{
  impl = new SceneContextImpl();
}

SceneContext::~SceneContext()
{
  delete impl;
}

DrawingContext&
SceneContext::color()
{
  return impl->color;
}

DrawingContext&
SceneContext::light()
{
  return impl->light;
}

DrawingContext&
SceneContext::highlight()
{
  return impl->highlight;
}

void
SceneContext::translate(float x, float y)
{
  impl->color.translate(x, y);
  impl->light.translate(x, y);
  impl->highlight.translate(x, y);
}

void
SceneContext::rotate(float angel)
{
  impl->color.rotate(angel);
  impl->light.rotate(angel);
  impl->highlight.rotate(angel);
}

void
SceneContext::scale(float x, float y)
{
  impl->color.scale(x, y);
  impl->light.scale(x, y);
  impl->highlight.scale(x, y);
}

void
SceneContext::push_modelview()
{
  impl->color.push_modelview();
  impl->light.push_modelview();
  impl->highlight.push_modelview();
}

void
SceneContext::pop_modelview()
{
  impl->color.pop_modelview();
  impl->light.pop_modelview();
  impl->highlight.pop_modelview();
}

void
SceneContext::reset_modelview()
{
  impl->color.reset_modelview();
  impl->light.reset_modelview();
  impl->highlight.reset_modelview();
}

void
SceneContext::render()
{
  SDL_Renderer* renderer = Display::get_renderer();
  if (!renderer)
    return;

  int w = Display::get_width();
  int h = Display::get_height();
  if (w <= 0 || h <= 0)
    return;

  impl->ensure_targets(renderer, w, h);
  if (!impl->color_tex || !impl->light_tex || !impl->highlight_tex)
    {
      // Fallback: color only
      impl->color.render(renderer);
      impl->color.clear();
      impl->light.clear();
      impl->highlight.clear();
      return;
    }

  // --- Color buffer ---
  SDL_SetRenderTarget(renderer, impl->color_tex);
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);
  impl->color.render(renderer);

  // --- Light buffer (ambient + light sprites) ---
  SDL_SetRenderTarget(renderer, impl->light_tex);
  // Default ambient if nothing was queued: dark blue night
  SDL_SetRenderDrawColor(renderer, 50, 50, 100, 255);
  SDL_RenderClear(renderer);
  // DrawingContext light requests (fill_screen + sprites) drawn on top
  impl->light.render(renderer);

  // --- Highlight buffer ---
  SDL_SetRenderTarget(renderer, impl->highlight_tex);
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
  SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
  SDL_RenderClear(renderer);
  impl->highlight.render(renderer);

  // --- Composite onto the window ---
  SDL_SetRenderTarget(renderer, nullptr);

  // 1. Color
  SDL_SetTextureBlendMode(impl->color_tex, SDL_BLENDMODE_NONE);
  SDL_RenderCopy(renderer, impl->color_tex, nullptr, nullptr);

  // 2. Multiply by lightmap (night + local lights)
  SDL_SetTextureBlendMode(impl->light_tex, SDL_BLENDMODE_MOD);
  SDL_RenderCopy(renderer, impl->light_tex, nullptr, nullptr);

  // 3. Additive highlights
  SDL_SetTextureBlendMode(impl->highlight_tex, SDL_BLENDMODE_ADD);
  SDL_RenderCopy(renderer, impl->highlight_tex, nullptr, nullptr);

  impl->color.clear();
  impl->light.clear();
  impl->highlight.clear();
}

/* EOF */
