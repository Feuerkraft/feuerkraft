//  $Id: vehicle_view.hxx,v 1.10 2003/06/04 13:10:09 grumbel Exp $
// 
//  Feuerkraft - A Tank Battle Game
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

#ifndef HEADER_FEUERKRAFT_VEHICLEVIEWUPDATER_HH
#define HEADER_FEUERKRAFT_VEHICLEVIEWUPDATER_HH

#include "vehicle.hxx"
#include "view.hxx"

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
};

#endif

/* EOF */
