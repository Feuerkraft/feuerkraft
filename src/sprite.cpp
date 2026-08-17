// Feuerkraft - A Tank Battle Game
// Copyright (C) 2026 Ingo Ruhnke <grumbel@gmail.com>

#include <iostream>
#include <SDL_image.h>
#include "sprite.hpp"
#include "display.hpp"

Sprite::Sprite()
  : current_frame(0), angle(0), alpha(1.0f),
    scale_x(1.0f), scale_y(1.0f), anim_time(0), frame_delay(0.1f), origin(origin_center),
    color(1.0f, 1.0f, 1.0f, 1.0f)
{
}

Sprite::Sprite(const std::string& filename)
  : current_frame(0), angle(0), alpha(1.0f),
    scale_x(1.0f), scale_y(1.0f), anim_time(0), frame_delay(0.1f), origin(origin_center),
    color(1.0f, 1.0f, 1.0f, 1.0f)
{
  load_frame(filename);
}

Sprite::Sprite(SDL_Texture* texture, int width, int height)
  : current_frame(0), angle(0), alpha(1.0f),
    scale_x(1.0f), scale_y(1.0f), anim_time(0), frame_delay(0.1f), origin(origin_center),
    color(1.0f, 1.0f, 1.0f, 1.0f)
{
  if (texture)
    {
      Frame f;
      f.texture = texture;
      f.width = width;
      f.height = height;
      frames.push_back(f);
    }
}

Sprite::Sprite(const Sprite& other)
  : current_frame(other.current_frame),
    angle(other.angle), alpha(other.alpha),
    scale_x(other.scale_x), scale_y(other.scale_y),
    anim_time(other.anim_time), frame_delay(other.frame_delay),
    origin(other.origin), color(other.color)
{
  // Share textures (no deep copy of GPU resources). Refcounting would
  // be nicer long-term; for the port this is acceptable.
  frames = other.frames;
}

Sprite&
Sprite::operator=(const Sprite& other)
{
  if (this == &other)
    return *this;
  // Do not free frames — they may be shared
  frames = other.frames;
  current_frame = other.current_frame;
  angle = other.angle;
  alpha = other.alpha;
  scale_x = other.scale_x;
  scale_y = other.scale_y;
  anim_time = other.anim_time;
  frame_delay = other.frame_delay;
  origin = other.origin;
  color = other.color;
  return *this;
}

Sprite::~Sprite()
{
  // Textures are owned by ResourceManager / shared; do not destroy here.
}

void
Sprite::load_frame(const std::string& filename)
{
  SDL_Renderer* renderer = Display::get_renderer();
  if (!renderer)
    {
      std::cerr << "Sprite: no renderer when loading " << filename << std::endl;
      return;
    }

  // Prefer RWops so Android APK assets work (fopen cannot read assets/).
  SDL_Surface* surface = nullptr;
  SDL_RWops* rw = SDL_RWFromFile(filename.c_str(), "rb");
  if (rw)
    surface = IMG_Load_RW(rw, 1); // frees rw
  else
    surface = IMG_Load(filename.c_str());
  if (!surface)
    {
      std::cerr << "Sprite: failed to load " << filename
                << ": " << IMG_GetError() << std::endl;
      return;
    }

  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
  int w = surface->w;
  int h = surface->h;
  SDL_FreeSurface(surface);

  if (!texture)
    {
      std::cerr << "Sprite: CreateTexture failed for " << filename
                << ": " << SDL_GetError() << std::endl;
      return;
    }

  SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
  // Linear filtering matches ClanLib-GL light cones / scaled sprites
  #if SDL_VERSION_ATLEAST(2, 0, 12)
  SDL_SetTextureScaleMode(texture, SDL_ScaleModeLinear);
  #endif

  Frame f;
  f.texture = texture;
  f.width = w;
  f.height = h;
  frames.push_back(f);
}

void
Sprite::add_frame(const std::string& filename)
{
  load_frame(filename);
}

int
Sprite::get_width() const
{
  if (frames.empty()) return 0;
  return frames[current_frame].width;
}

int
Sprite::get_height() const
{
  if (frames.empty()) return 0;
  return frames[current_frame].height;
}

void
Sprite::set_frame(int frame)
{
  if (frames.empty()) return;
  if (frame < 0) frame = 0;
  if (frame >= static_cast<int>(frames.size()))
    frame = static_cast<int>(frames.size()) - 1;
  current_frame = frame;
}

void
Sprite::set_angle(float degrees)
{
  angle = degrees;
}

void
Sprite::set_alpha(float a)
{
  alpha = a;
}

void
Sprite::set_scale(float x, float y)
{
  scale_x = x;
  scale_y = y;
}

void
Sprite::set_alignment(Origin o)
{
  origin = o;
}

void
Sprite::set_color(const Color& c)
{
  color = c;
}

void
Sprite::draw(float x, float y) const
{
  if (frames.empty()) return;
  SDL_Renderer* renderer = Display::get_renderer();
  if (!renderer) return;

  const Frame& f = frames[current_frame];
  float w = f.width  * scale_x;
  float h = f.height * scale_y;

  SDL_Rect dst;
  if (origin == origin_center)
    {
      dst.x = static_cast<int>(x - w / 2);
      dst.y = static_cast<int>(y - h / 2);
    }
  else
    {
      dst.x = static_cast<int>(x);
      dst.y = static_cast<int>(y);
    }
  dst.w = static_cast<int>(w);
  dst.h = static_cast<int>(h);

  SDL_SetTextureAlphaMod(f.texture, static_cast<Uint8>(alpha * color.alpha * 255));
  SDL_SetTextureColorMod(f.texture,
                         static_cast<Uint8>(color.red   * 255),
                         static_cast<Uint8>(color.green * 255),
                         static_cast<Uint8>(color.blue  * 255));

  SDL_RenderCopyEx(renderer, f.texture, nullptr, &dst,
                   angle, nullptr, SDL_FLIP_NONE);
}


void
Sprite::update(float delta)
{
  if (frames.size() <= 1 || frame_delay <= 0.0f)
    return;
  anim_time += delta;
  while (anim_time >= frame_delay)
    {
      anim_time -= frame_delay;
      current_frame = (current_frame + 1) % static_cast<int>(frames.size());
    }
}

/* EOF */
