// Feuerkraft - A Tank Battle Game
// Copyright (C) 2000 Ingo Ruhnke <grumbel@gmail.com>
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

#ifndef VEHICLE_HH
#define VEHICLE_HH

#include "../unit.hpp"

class Controller;
class Projectile;

class Vehicle : public Unit
{
protected:
  float velocity;

  float ammo;
  float fuel;

  // Controll variables
  float acceleration;
  float steering;
  float strafe_steering;

  bool firing;
  bool secondary_firing;
public:
  Vehicle ();
  virtual ~Vehicle () {}

  virtual void update_controlls(const Controller&);

  virtual float get_velocity() { return velocity; }

  /** Sets the current turn of the vehicle, \a turn needs to be in
      range of [-1.0, 1.0] */
  void set_turn(float turn);

  /** Sets the current acceleration, \a accel must be in range of
      [-1.0, 1.0] (full break, full acceleration) */
  void set_acceleration(float accel);

  virtual float get_ammo();
  virtual float get_fuel();

  virtual void  refuel(float delta);
  virtual void  reload_ammo(float delta);

  virtual void collide (Projectile*) {}
};

typedef Vehicle* VehiclePtr;

#endif

/* EOF */

