//  $Id: Radar.cxx,v 1.7 2002/04/02 09:52:56 grumbel Exp $
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

#include "buildings/BuildingMap.hxx"
#include "Radar.hxx"
#include "ResourceManager.hxx"

Radar::Radar (const CL_Vector& arg_pos, 
	      boost::dummy_ptr<GameWorld> w,
	      boost::dummy_ptr<Vehicle> v)
  : world (w),
    vehicle (v),
    background (resources->get_sprite("feuerkraft/radar")),
    pos (arg_pos),
    angle (0)
{
  radar_line = resources->get_sprite ("feuerkraft/radar_line");
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

  background.draw (int(pos.x), int(pos.y));
  
  std::list<GameObj*>& objs = world->get_objects ();
  for (GameWorld::ObjIter i = objs.begin (); i != objs.end (); ++i)
    {
      Vehicle* vehicle = dynamic_cast<Vehicle*>(*i);
      if (vehicle && vehicle != this->vehicle.get ()) draw_vehicle (vehicle);
    }

  world->get_buildingmap ()->draw_radar (this);

  radar_line.set_rotate (angle/3.1415927*180.0f + 180.0f);
  radar_line.draw (int(pos.x), int(pos.y));
  //FIXME:Display2: frame support removed 
  /*
  CL_Display::draw_line (int(pos.x), int(pos.y), int(pos.x) - 45, int(pos.y) - 45,
			 1.0, 1.0, 0.0);

  CL_Display::draw_line (int(pos.x), int(pos.y), int(pos.x) + 45, int(pos.y) - 45,
			 1.0, 1.0, 0.0);

  CL_Display::draw_line (int(pos.x), int(pos.y), int(end.x), int(end.y),
			 0.0, 1.0, 0.0);
  */
}

void
Radar::draw_blip (const CL_Vector& arg_pos, int size,
		  float red, float green, float blue)
{
  // Callculate the distance between 'pos' and the vehicle that holds
  // the radar
  CL_Vector diff = arg_pos;
  diff -= vehicle->get_pos ();
  diff *= 1/30.0f;

  float alpha = (diff.norm () / 64.0);
  alpha *= alpha * alpha;
  alpha = 1.0f - alpha;

  if (diff.norm () < 64.0)
    {
      diff = diff.rotate (-vehicle->get_angle () + (3.14159/2), CL_Vector (0, 0, 1.0));

      //FIXME:Display2: frame support removed 
      /*
      CL_Display::fill_rect (int(pos.x + diff.x), int(pos.y + diff.y),
			     int(pos.x + diff.x) + size, int(pos.y + diff.y) + size,
			     red, green, blue, alpha);*/
    }
}

void 
Radar::draw_vehicle (boost::dummy_ptr<Vehicle> obj)
{
  draw_blip(obj->get_pos (), int(obj->get_physical_size ()));
}

void 
Radar::update (float delta)
{
  angle += 10.0f * delta;
}

/* EOF */
