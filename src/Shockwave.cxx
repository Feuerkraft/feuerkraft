//  $Id: Shockwave.cxx,v 1.3 2002/03/10 23:55:59 grumbel Exp $
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

#include "Shockwave.hxx"

Shockwave::Shockwave (boost::dummy_ptr<GameWorld>  w, CL_Vector arg_pos) 
  : GameObj (w),
    pos (arg_pos)
{
  progress = 0;
  sprite = new Sprite (new SpriteProvider ("feuerkraft/shockwave", resources));
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
Shockwave::draw (View* view)
{
  sprite->setAlpha(1.0f - (progress/10.0f));
  sprite->setScale(progress + .5);
  view->draw (sprite, pos);
}

void 
Shockwave::update (float delta)
{
  progress += delta * 10.0f;
  if (progress >= 10.0)
    remove ();
}

/* EOF */
