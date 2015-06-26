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

#ifndef HEADER_FEUERKRAFT_VEHICLEVIEWUPDATER_HH
#define HEADER_FEUERKRAFT_VEHICLEVIEWUPDATER_HH

#include "vehicles/vehicle.hpp"
#include "view.hpp"

// FIXME: Rename to UnitViewUpdater
class VehicleViewUpdater : public ViewUpdater
{
private:
  Unit* unit;
  FloatVector2d pos;

  float speed;
  float zoom_follower;

public:
  VehicleViewUpdater (Unit* arg_unit);
  virtual ~VehicleViewUpdater ();

  virtual void update(float delta, ViewState& state);
  void set_unit(Unit* arg_unit);

private:
  VehicleViewUpdater(const VehicleViewUpdater&);
  VehicleViewUpdater& operator=(const VehicleViewUpdater&);
};

#endif

/* EOF */
