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

#ifndef HEADER_DRAWING_REQUEST_HXX
#define HEADER_DRAWING_REQUEST_HXX

#include <SDL.h>
#include "math_types.hpp"

/**
 * Base class for deferred drawing commands.
 */
class DrawingRequest
{
protected:
  Vector3f pos;
public:
  DrawingRequest(const Vector3f& pos_) : pos(pos_) {}
  virtual ~DrawingRequest() {}

  virtual void draw(SDL_Renderer* renderer) = 0;

  /** Returns true if the request contains an alpha channel and needs
      to be drawn in order */
  virtual bool has_alpha() { return true; }

  /** Returns the position at which the request should be drawn */
  virtual float get_z_pos() { return pos.z; }
private:
  DrawingRequest (const DrawingRequest&);
  DrawingRequest& operator= (const DrawingRequest&);
};

#endif

/* EOF */
