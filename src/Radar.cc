//  $Id: Radar.cc,v 1.1 2001/05/01 10:44:54 grumbel Exp $
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

#include "Radar.hh"

Radar::Radar (const CL_Vector& arg_pos, 
	      boost::dummy_ptr<GameWorld> w,
	      boost::dummy_ptr<Vehicle> v)
  : world (w),
    vehicle (v),
    background ("feuerkraft/radar", resources),
    pos (arg_pos),
    angle (0)
{
  
}

Radar::~Radar ()
{
}

void 
Radar::draw ()
{
  CL_Vector end (0.0f, 64.0f);

  end = end.rotate (angle, CL_Vector (0, 0, 1.0f));

  end += pos;

  background.put_screen (int(pos.x - (background.get_width ()/2)),
			 int(pos.y - (background.get_height ()/2)));
  
  std::list<boost::shared_ptr<GameObj> > objs = world->get_objects ();
  for (GameWorld::ObjIter i = objs.begin (); i != objs.end (); ++i)
    {
      Vehicle* vehicle = dynamic_cast<Vehicle*>((*i).get());
      if (vehicle) draw_vehicle (vehicle);
    }

  CL_Display::draw_line (int(pos.x), int(pos.y), int(end.x), int(end.y),
			 0.0, 1.0, 0.0);
}

void 
Radar::draw_vehicle (boost::dummy_ptr<Vehicle> obj)
{
  CL_Vector diff = obj->get_pos () - vehicle->get_pos ();
  diff *= 1/10.0;
 
  if (diff.norm () < 64.0)
    CL_Display::fill_rect (int(pos.x + diff.x), int(pos.y + diff.y),
			   int(pos.x + diff.x) + 3, int(pos.y + diff.y) + 3,
			   1.0, 0.0, 0.0);
}

void 
Radar::update (float delta)
{
  angle += 0.1 * delta;
}

/* EOF */
