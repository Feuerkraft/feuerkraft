// Feuerkraft - A Tank Battle Game
// Copyright (C) 2026 Ingo Ruhnke <grumbel@gmail.com>
//
// SDL2-backed sprite (replacement for CL_Sprite).

#ifndef HEADER_SPRITE_HXX
#define HEADER_SPRITE_HXX

#include <string>
#include <vector>
#include <SDL.h>
#include "color.hpp"

enum Origin
{
  origin_top_left,
  origin_top_center,
  origin_center
};

enum BlendFunc
{
  blend_src_alpha,
  blend_one,
  blend_zero,
  blend_dst_color
};

/**
 * A sprite holds one or more texture frames and can be drawn with
 * rotation, scaling and alpha.
 */
class Sprite
{
public:
  Sprite();
  /** Load a single image file as a one-frame sprite. */
  explicit Sprite(const std::string& filename);
  /** Construct from an already-created texture (takes ownership). */
  Sprite(SDL_Texture* texture, int width, int height);

  Sprite(const Sprite& other);
  Sprite& operator=(const Sprite& other);
  ~Sprite();

  bool is_null() const { return frames.empty(); }

  int get_width()  const;
  int get_height() const;
  int get_frame_count() const { return static_cast<int>(frames.size()); }

  void set_frame(int frame);
  int  get_frame() const { return current_frame; }

  void set_angle(float degrees);
  float get_angle() const { return angle; }

  void set_alpha(float alpha);
  float get_alpha() const { return alpha; }

  void set_scale(float x, float y);
  float get_scale_x() const { return scale_x; }
  float get_scale_y() const { return scale_y; }
  void set_alignment(Origin origin);

  void set_color(const Color& c);

  /** Draw at the given screen position (alignment applied). */
  void draw(float x, float y) const;
  void draw(int x, int y) const { draw(static_cast<float>(x), static_cast<float>(y)); }
  // Compatibility overload (renderer arg ignored; uses Display::get_renderer())
  void draw(float x, float y, void*) const { draw(x, y); }
  void draw(int x, int y, void* p) const { draw(static_cast<float>(x), static_cast<float>(y), p); }

  /** Advance animation by delta seconds (multi-frame sprites). */
  void update(float delta);

  /** No-op blend func stub (SDL_Texture uses fixed blend mode). */
  void set_blend_func(BlendFunc, BlendFunc) {}

  /** Rotate by degrees (adds to current angle). */
  void rotate(float degrees) { angle += degrees; }

  explicit operator bool() const { return !frames.empty(); }

  /** Add an extra frame from a file (for multi-frame sprites). */
  void add_frame(const std::string& filename);

private:
  struct Frame
  {
    SDL_Texture* texture;
    int width;
    int height;
  };

  std::vector<Frame> frames;
  int current_frame;
  float angle;   // degrees
  float alpha;
  float scale_x;
  float scale_y;
  float anim_time;
  float frame_delay; // seconds per frame
  Origin origin;
  Color color;

  void load_frame(const std::string& filename);
  void free_frames();
};

#endif

/* EOF */
