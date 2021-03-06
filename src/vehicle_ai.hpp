// Feuerkraft - A Tank Battle Game
// Copyright (C) 2002 Ingo Ruhnke <grumbel@gmail.com>
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

#ifndef HEADER_VEHICLE_AI_HXX
#define HEADER_VEHICLE_AI_HXX

#include "line_segments.hpp"
#include "input/controller.hpp"
#include "ai.hpp"
#include "vehicles/vehicle.hpp"

/** class for AI driven vehicles */
class VehicleAI : public AI
{
protected:
  Vehicle* vehicle;
public:
  VehicleAI(Vehicle* vehicle);
  virtual ~VehicleAI() {};
  GameObj* get_object() { return vehicle; }

private:
  VehicleAI(const VehicleAI&);
  VehicleAI& operator=(const VehicleAI&);
};

/** class for robot like ai which controlls a vehicle with physic
    simulation switched on */
class VehicleRoboAI : public VehicleAI
{
private:
  Controller controller;
  float ai_count;
public:
  VehicleRoboAI(Vehicle*);
  void update(float delta);
};

/** AI class that lets drive a vehicle streight on a simple path */
class VehiclePathAI : public VehicleAI
{
private:
  bool  driving;
  float length;
  LineSegments line_segments;
public:
  VehiclePathAI(Vehicle*);

  void drive_to(const FloatVector2d& pos);
  void update(float delta);

private:
  VehiclePathAI(const VehiclePathAI&);
  VehiclePathAI& operator=(const VehiclePathAI&);
};

#endif

/* EOF */
