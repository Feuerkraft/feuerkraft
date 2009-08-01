//  $Id: player.hpp,v 1.6 2003/06/17 22:06:13 grumbel Exp $
// 
//  Feuerkraft - A Tank Battle Game
//  Copyright (C) 2002 Ingo Ruhnke <grumbel@gmx.de>
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//  
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//  
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.

#ifndef HEADER_PLAYER_HXX
#define HEADER_PLAYER_HXX

class Unit;

/** The player class keeps track of all the stuff that is owned by a
    player (Controller, Unit, UnitView, etc) */
class Player
{
private:
  /** The soldier unit representing the player, after player death it
      might change/respawn */
  Unit* soldier;

  /** The currently active units that gets input events (vehicle,
      heli, soldier, etc.) */
  Unit* unit;

public:
  Player(Unit* unit);

  Unit* get_soldier();
  
  /** Set the current soldier of the player */
  void set_soldier(Unit* new_soldier);

  void  set_current_unit(Unit*);
  Unit* get_current_unit();

private:
  Player (const Player&);
  Player& operator= (const Player&);
};

typedef Player* PlayerPtr;

#endif

/* EOF */
