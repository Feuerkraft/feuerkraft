//  $Id: fire_particle.cpp,v 1.2 2003/06/08 15:31:27 grumbel Exp $
//
//  Pingus - A free Lemmings clone
//  Copyright (C) 2002 Ingo Ruhnke <grumbel@gmx.de>
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include <ClanLib/Display/color.h>
#include "../math.hpp"
#include "../view.hpp"
#include "../resource_manager.hpp"
#include "fire_particle.hpp"

FireParticle::FireParticle(const FloatVector2d& arg_pos)
  : sprite(resources->get_sprite("feuerkraft/firep")),
    pos(arg_pos),
    life_time(0)
{
  sprite.set_angle(Math::rad2deg(Math::frand() * Math::pi*2));
  sprite.set_blend_func(blend_src_alpha, blend_one);
}

void
FireParticle::update(float delta)
{
  pos += GameWorld::current()->get_wind() * delta * 1.3f;

  life_time += delta;

  if (life_time > .33f)
    {
      life_time = .33f;
      remove();
    }

  // black  CL_Color(  0,   0,   0);
  // red    CL_Color(255,   0,   0);
  // yellow CL_Color(255, 255,   0);
  // white  CL_Color(255, 255, 255);

  float factor = life_time * 3.0f;

  CL_Color color(life_time >= 0.75 ? 255 : int(255 * (life_time - 0.75f)/0.25f),
                 int(factor * 255),
                 life_time >= 0.25 ? 255 : int(255 * (life_time - 0.25f)/0.75f));
  sprite.set_color(color);
  sprite.set_alpha(1.0f - factor);
  sprite.set_scale(1.0 - factor/2, 1.0 - factor/2);
}

void
FireParticle::draw (View& view)
{
  view.get_sc().color().draw(sprite, pos.x, pos.y);
}

/* EOF */
