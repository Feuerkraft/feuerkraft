//  $Id: base.cxx,v 1.5 2003/05/18 09:38:44 grumbel Exp $
//
//  Pingus - A free Lemmings clone
//  Copyright (C) 2000 Ingo Ruhnke <grumbel@gmx.de>
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

#include "../radar.hxx"
#include "../resource_manager.hxx"
#include "base.hxx"

Base::Base (const BaseData& data)
  : Building (data.x_pos, data.y_pos),
    sprite (resources->get_sprite("feuerkraft/start")),
    pos (data.x_pos * 40 + 40, data.y_pos * 40 + 40) // FIXME: tilesize hardcoded
{
  x_pos = data.x_pos;
  y_pos = data.y_pos;
}

Base::~Base ()
{
}

void
Base::draw (ViewPtr view)
{
  view->draw (&sprite, pos);
}

void
Base::draw_radar (RadarPtr radar)
{
  radar->draw_blip (pos, 4);
}

void
Base::update (float delta)
{
}

/* EOF */
