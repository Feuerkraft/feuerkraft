//  $Id: Base.cxx,v 1.3 2002/03/26 16:46:36 grumbel Exp $
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

#include "../Radar.hxx"
#include "Base.hxx"

// FIXME: hack... replace this with better resource handling
extern SpriteProviderStorage* storage;
extern CL_ResourceManager* resources;

Base::Base (boost::dummy_ptr<GameWorld>  w, const BaseData& data)
  : Building (w),
    BaseData (data),
    sprite (storage->get("feuerkraft/start")),
    pos (x_pos * 40 + 40, y_pos * 40 + 40) // FIXME: tilesize hardcoded
{
}

Base::~Base ()
{
}

void
Base::draw (boost::dummy_ptr<View> view)
{
  view->draw (&sprite, pos);
}

void
Base::draw_radar (boost::dummy_ptr<Radar> radar)
{
  radar->draw_blip (pos, 4);
}

void
Base::update (float delta)
{
}

/* EOF */
