// Feuerkraft - A Tank Battle Game
// Copyright (C) 2000 Ingo Ruhnke <grumbel@gmail.com>
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

#include "view.hpp"
#include "shockwave.hpp"
#include "resource_manager.hpp"

Shockwave::Shockwave(FloatVector2d arg_pos)
  : pos (arg_pos)
{
  progress = 0;
  sprite = resources->get_sprite ("feuerkraft/shockwave");
}

Shockwave::~Shockwave ()
{
}

template<class T>
T mid (T min, T some, T max)
{
  return std::min(std::max(min, some), max);
}

void
Shockwave::draw(View& view)
{
  sprite.set_alpha(1.0f - (progress/10.0f));
  sprite.set_scale(progress + .5, progress + .5);
  view.get_sc().color().draw(sprite, pos.x, pos.y);
}

void
Shockwave::update (float delta)
{
  progress += delta * 10.0f;
  if (progress >= 10.0)
    remove ();
}

/* EOF */
