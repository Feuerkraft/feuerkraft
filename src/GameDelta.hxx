//  $Id: GameDelta.hxx,v 1.1 2002/03/10 19:56:00 grumbel Exp $
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

#ifndef GAMEDELTA_HXX
#define GAMEDELTA_HXX

/** The GameDelta class holds all informations that are required to
    bring the GameWorld from its current stage to its next stage,
    which means it will basically hold the time delta between frames,
    along with input that is to be passed to the game engine. A
    GameDelta is used as an argument to GameObj::update(). 

    GameDelta is used instead of a simple float because input should
    also be handled as argument to the update() function instead of
    reading it directly, this allows easy recording and playback of
    game sessions. */
class GameDelta
{
private:
  float time_delta;
  
public:
  /* Returns the controller which is bound to the given ControllerID

  Pseudo Code:
     
     Controller* get_controller (ControllerID id);
   */

  /** Number of seconds since the last update */
  float get_time ();
};

#endif

/* EOF */
