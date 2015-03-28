// Feuerkraft - A Tank Battle Game
// Copyright (C) 2002 Ingo Ruhnke <grumbel@gmx.de>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#ifndef HEADER_AI_VEHICLE_HXX
#define HEADER_AI_VEHICLE_HXX

#include <list>
#include "vector2d.hpp"
#include <ClanLib/Display/sprite.h>

#include "energie.hpp"
#include "line_segments.hpp"
#include "sequence_manager.hpp"
#include "vehicles/vehicle.hpp"

class SmokeEmitter;
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
class AIVehicle : public Vehicle
{
private:
  bool    destroyed;
  Energie energie;
  float   length;
  LineSegments line_segments;

  CL_Sprite sprite;
  CL_Sprite destroyed_sprite;
  std::list<AIVehicleOrder> orders;

  AIVehicleOrder current_order;
  SmokeEmitter* smoke_emitter;
public:
  AIVehicle(const FloatVector2d& arg_pos);

  void update(float delta);
  void draw (View& view);
  void draw_energie (View& view);
  void draw_levelmap (LevelMap& levelmap);

  void wait(float seconds);
  void drive_to(const FloatVector2d& pos);

  void add_order(AIVehicleOrder);
  void clear_orders();
  void next_order();

  void on_collision(GameObj* obj);
  void on_collision_with_building(Building* building);

  bool is_colliding(FloatVector2d) { return false; }
private:
  AIVehicle (const AIVehicle&);
  AIVehicle& operator= (const AIVehicle&);
};

#endif

/* EOF */
