//  $Id: radar.cxx,v 1.9 2003/05/19 19:00:56 grumbel Exp $
//
//  Pingus - A free Lemmings clone
//  Copyright(C) 2000 Ingo Ruhnke <grumbel@gmx.de>
//
//  This program is free software; you can redistribute it and/or
//  modify it under the terms of the GNU General Public License
//  as published by the Free Software Foundation; either version 2
//  of the License, or(at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program; if not, write to the Free Software
//  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

#include <ClanLib/Display/display.h>
#include "buildings/building_map.hxx"
#include "game_obj_manager.hxx"
#include "radar.hxx"
#include "math.hxx"
#include "player.hxx"
#include "vehicle.hxx"
#include "resource_manager.hxx"

Radar::Radar(const FloatVector2d& arg_pos, 
             PlayerPtr p)
  : player(p),
    background(resources->get_sprite("feuerkraft/radar")),
    pos(arg_pos),
    angle(0)
{
}

Radar::~Radar()
{
}

void 
Radar::draw(CL_GraphicContext* gc)
{
  FloatVector2d end(0.0f, 64.0f);

  end = end.rotate(angle);

  end += pos;

  background.draw(int(pos.x), int(pos.y), gc);
  
  GameObjManager* objs = GameWorld::current()->get_game_obj_manager();
  for (GameObjManager::iterator i = objs->begin(); i != objs->end(); ++i)
    {
      Vehicle* vehicle = dynamic_cast<Vehicle*>(*i);
      if (vehicle)
        draw_vehicle(*vehicle);
    }

  GameWorld::current()->get_buildingmap()->draw_radar(*this);

  CL_Display::draw_line(int(pos.x), int(pos.y - 5),
                        int(pos.x), int(pos.y + 5),
                        CL_Color(0, 255, 0));

  CL_Display::draw_line(int(pos.x - 5), int(pos.y),
                        int(pos.x + 5), int(pos.y),
                        CL_Color(0, 255, 0));
}

void
Radar::draw_blip(const FloatVector2d& arg_pos, int size,
		  float red, float green, float blue)
{
  // Callculate the distance between 'pos' and the vehicle that holds
  // the radar
  FloatVector2d diff = arg_pos;
  diff -= player->get_current_vehicle()->get_pos();
  diff *= 1/30.0f;

  float alpha =(diff.get_length() / 64.0);
  alpha *= alpha * alpha;
  alpha = 1.0f - alpha;

  if (diff.get_length() < 64.0)
    {
      //diff = diff.rotate(-vehicle->get_angle () + (3.14159/2), FloatVector2d (0, 0, 1.0));

      CL_Display::fill_rect(CL_Rect(int(pos.x + diff.x), int(pos.y + diff.y),
                                     int(pos.x + diff.x) + size, int(pos.y + diff.y) + size),
			     CL_Color(int(255*red),
                                      int(255*green),
                                      int(255*blue), 
                                      int(255*alpha)));
    }
}

void 
Radar::draw_vehicle(Vehicle& obj)
{
  draw_blip(obj.get_pos(), int(obj.get_physical_size ()));
}

void 
Radar::update(float delta)
{
  angle += 10.0f * delta;
}

/* EOF */
