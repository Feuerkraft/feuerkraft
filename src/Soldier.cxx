//  $Id: Soldier.cxx,v 1.2 2001/12/12 00:25:10 grumbel Exp $
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

#include <ClanLib/core.h>
#include "Soldier.hxx"

Soldier::Soldier (boost::dummy_ptr<GameWorld>  w, const CL_Vector& arg_pos) 
  : Vehicle (w),
    sur ("feuerkraft/soldier", resources),
    frame (0)
{
  pos = arg_pos;
}

Soldier::~Soldier ()
{
}

void 
Soldier::draw (View* view)
{
  view->draw (sur, int(pos.x), 
	      int(pos.y), frame);
}

void 
Soldier::update (float delta)
{
  if (++step > 5)
    {
      step = 0;
      frame = (frame + 1) % sur.get_num_frames ();
    }

  pos += CL_Vector (0.0, -0.5, 0.0);
}

bool 
Soldier::is_colliding(CL_Vector obj_pos)
{
  CL_Vector diff = obj_pos - pos;
  if (diff.norm () > 5)
    return false;
  else
    return true;
}

/* EOF */
