//  $Id: unit.hxx,v 1.4 2003/06/04 10:59:00 grumbel Exp $
// 
//  Feuerkraft - A Tank Battle Game
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

#ifndef HEADER_FEUERKRAFT_UNIT_HXX
#define HEADER_FEUERKRAFT_UNIT_HXX

#include "game_obj.hxx"
#include "vector2d.hxx"
#include "input/input_event.hxx"

/** A unit is a vehicle, a solidier or a gun tower that the player can
    controll */
class Unit : public GameObj
{
protected:
  /** Position of the unit in world-coordinates */
  FloatVector2d pos;

  /** Orientation of the unit */
  float orientation;

public:
  Unit();
  ~Unit();
  
  /** Feed new input events into the unit, allowing it to move
      accordingly */
  virtual void update_controlls(const InputEventLst& events) =0;

  FloatVector2d get_pos() { return pos; }
  float get_orientation() { return orientation; }

  void set_position(const FloatVector2d& new_pos);
  void set_orientation(float new_orientation);

  float get_orientation() const { return orientation; }
  FloatVector2d get_position() const { return pos; }
  
private:
  Unit (const Unit&);
  Unit& operator= (const Unit&);
};

#endif

/* EOF */
