//  $Id: vehicle.hxx,v 1.7 2003/05/30 22:44:53 grumbel Exp $
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

#ifndef VEHICLE_HH
#define VEHICLE_HH

#include "game_obj.hxx"
#include "vector2d.hxx"

class Projectile;

/** FIXME: Wrong name for this kind of class, better rename it at some point */
class Vehicle : public GameObj
{
protected:
  FloatVector2d pos;
  
  float orientation;
  float velocity;

  float ammo;
  float fuel;
public:
  Vehicle ();
  virtual ~Vehicle () {}

  FloatVector2d get_pos() { return pos; }
  virtual float get_angle() { return 0.0; }
  virtual float get_ammo();
  virtual float get_fuel();
  virtual void  refuel(float delta);
  virtual void  reload_ammo(float delta);
  virtual float get_velocity() { return 0.0; };

  virtual void collide (Projectile*) {}
};

typedef Vehicle* VehiclePtr;

#endif

/* EOF */

