//  $Id: ai_vehicle.hxx,v 1.10 2003/05/18 21:15:06 grumbel Exp $
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

#ifndef HEADER_AI_VEHICLE_HXX
#define HEADER_AI_VEHICLE_HXX

#include <list>
#include "vector2d.hxx"
#include <ClanLib/Display/sprite.h>

#include "energie.hxx"
#include "line_segments.hxx"
#include "sequence_manager.hxx"
#include "game_obj.hxx"

class LevelMap;

struct Position
{
  float x;
  float y;
};

enum AIVehicleOrderType { 
  AI_VO_NONE, 
  AI_VO_DRIVETO, 
  AI_VO_WAIT, 
  AI_VO_CONTINUE
}; 

struct AIVehicleOrderNone
{
};

struct AIVehicleOrderDriveTo
{
  int sequence_id;

  Position pos;
};

struct AIVehicleOrderWait
{
  int sequence_id;

  /** Number of seconds to wait, -1 means forever, until next order is
      given */
  float seconds;
};

struct AIVehicleOrder
{
  AIVehicleOrderType type;

  union {
    AIVehicleOrderDriveTo  drive_to;
    AIVehicleOrderWait     wait;
    AIVehicleOrderNone     none;
  };
};

/** */
class AIVehicle : public GameObj
{
private:
  bool destroyed;
  Energie energie;
  FloatVector2d pos;
  float length;
  LineSegments line_segments;

  float orientation;
  float velocity;

  CL_Sprite sprite;
  CL_Sprite destroyed_sprite;
  std::list<AIVehicleOrder> orders;

  AIVehicleOrder current_order;
public:
  AIVehicle(const FloatVector2d& arg_pos);

  void update(float delta);
  void draw (View* view);
  void draw_energie (View* view);
  void draw_levelmap (LevelMap* levelmap);

  void wait(float seconds);
  void drive_to(const FloatVector2d& pos);

  void add_order(AIVehicleOrder);
  void clear_orders();
  void next_order();

  void on_collision(GameObj* obj);
  void on_collision_with_building(Building* building);
private:
  AIVehicle (const AIVehicle&);
  AIVehicle& operator= (const AIVehicle&);
};

#endif

/* EOF */
