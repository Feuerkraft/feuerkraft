//  $Id: marker.cpp,v 1.3 2003/06/23 09:56:39 grumbel Exp $
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

#include "property_set.hpp"
#include "resource_manager.hpp"
#include "marker.hpp"
#include "alist.hpp"
#include "radar.hpp"
#include "view.hpp"

Marker::Marker(const AList& lst)
{
  passed_time = 0;
  properties->register_float("x-pos", &pos.x);
  properties->register_float("y-pos", &pos.y);

  pos.x = lst.get_float("x-pos");
  pos.y = lst.get_float("y-pos");

  sprite = resources->get_sprite("feuerkraft/marker");
  sprite.set_blend_func(blend_src_alpha, blend_one);
}

Marker::~Marker()
{
}

void
Marker::draw (View& view)
{
  view.get_sc().color().draw(sprite, pos.x, pos.y);
}

void
Marker::draw_radar(Radar& radar)
{
  radar.draw_blip(pos, 3, 1.0f, 1.0f, 1.0f);
}

void
Marker::update(float delta)
{
  passed_time += delta;
  sprite.set_alpha(sin(passed_time * 7.0f) * .2 + .3);
}

/* EOF */
