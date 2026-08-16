// Feuerkraft - A Tank Battle Game
// Copyright (C) 2026 Ingo Ruhnke <grumbel@gmail.com>
//
// Minimal geometry types used by the display layer (replacement for
// ClanLib CL_Pointf / CL_Vector / CL_Rect).

#ifndef HEADER_DISPLAY_MATH_TYPES_HXX
#define HEADER_DISPLAY_MATH_TYPES_HXX

struct Pointf
{
  float x, y;
  Pointf() : x(0), y(0) {}
  Pointf(float x_, float y_) : x(x_), y(y_) {}
};

struct Vector3f
{
  float x, y, z;
  Vector3f() : x(0), y(0), z(0) {}
  Vector3f(float x_, float y_, float z_ = 0) : x(x_), y(y_), z(z_) {}
};

struct Rect
{
  int left, top, right, bottom;
  Rect() : left(0), top(0), right(0), bottom(0) {}
  Rect(int l, int t, int r, int b) : left(l), top(t), right(r), bottom(b) {}
  Rect(const Pointf& p, int w, int h)
    : left(static_cast<int>(p.x)), top(static_cast<int>(p.y)),
      right(static_cast<int>(p.x) + w), bottom(static_cast<int>(p.y) + h) {}
  int get_width()  const { return right - left; }
  int get_height() const { return bottom - top; }
};

#endif

/* EOF */
