//  $Id: Flag.cc,v 1.4 2001/05/04 17:11:08 grumbel Exp $
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

#include "Jeep.hh"
#include "Flag.hh"

extern CL_ResourceManager* resources;

Flag::Flag (boost::dummy_ptr<GameWorld>  w, CL_Vector arg_pos) 
  : GameObj (w),
    sur ("feuerkraft/blueflag", resources),
    pos (arg_pos)
{
}

Flag::~Flag ()
{
}

void 
Flag::draw (View* view)
{
  view->draw (sur, int(pos.x - 24), int(pos.y - 3));
}

void
Flag::update (float delta)
{
  for (std::list<boost::shared_ptr<GameObj> >::iterator 
	 j = world->get_objects ().begin ();
       j != world->get_objects ().end (); ++j)
    {
      Jeep* jeep = dynamic_cast<Jeep*>(j->get ());
      if (jeep && (pos - jeep->get_pos ()).norm () < 20.0f)
	{
	  jeep->add_flag (this);
	}
    }
}

/* EOF */
