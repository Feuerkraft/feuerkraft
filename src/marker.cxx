//  $Id: marker.cxx,v 1.1 2003/06/04 22:51:52 grumbel Exp $
//
//  Pingus - A free Lemmings clone
//  Copyright (C) 2002 Ingo Ruhnke <grumbel@gmx.de>
//
//  This program is free software; you can redistribute it and/or
//  modify it under the terms of the GNU General Public License
//  as published by the Free Software Foundation; either version 2
//  of the License, or (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program; if not, write to the Free Software
//  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

#include "property_set.hxx"
#include "resource_manager.hxx"
#include "marker.hxx"
#include "view.hxx"

Marker::Marker()
{
  passed_time = 0;
  properties->register_float("x-pos", &pos.x);
  properties->register_float("y-pos", &pos.y);

  sprite = resources->get_sprite("feuerkraft/marker");
  sprite.set_blend_func(blend_src_alpha, blend_one);
}

Marker::~Marker()
{
}

void
Marker::draw (View& view)
{
  view.draw(sprite, pos);
}

void
Marker::update(float delta)
{
  passed_time += delta;
  sprite.set_alpha(sin(passed_time * 7.0f) * .2 + .3);
}

/* EOF */
