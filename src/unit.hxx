//  $Id: unit.hxx,v 1.2 2003/05/18 21:15:06 grumbel Exp $
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

#ifndef HEADER_FEUERKRAFT_UNIT_HXX
#define HEADER_FEUERKRAFT_UNIT_HXX

/** A unit is a vehicle, a solidier or a gun tower that the player can
    controll */
class Unit
{
protected:
  /** Position of the unit in world-coordinates */
  FloatVector2d pos;

  /** Orientation of the unit */
  float orientation;
public:
  /** Sets the current turn of the vehicle, \a turn needs to be in
      range of [-1.0, 1.0] */
  void set_turn(float turn);

  /** Sets the current acceleration, \a accel must be in range of
      [-1.0, 1.0] (full break, full acceleration) */
  void set_acceleration(float accel);
  
private:
  Unit (const Unit&);
  Unit& operator= (const Unit&);
};

#endif

/* EOF */
