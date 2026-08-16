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
  origin_center
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
  void set_alignment(Origin origin);

  void set_color(const Color& c);

  /** Draw at the given screen position (alignment applied). */
  void draw(float x, float y) const;
  void draw(int x, int y) const { draw(static_cast<float>(x), static_cast<float>(y)); }

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
  Origin origin;
  Color color;

  void load_frame(const std::string& filename);
  void free_frames();
};

#endif

/* EOF */
