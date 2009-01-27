//  $Id: goal_manager.hpp,v 1.1 2003/06/18 13:05:35 grumbel Exp $
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

#ifndef HEADER_GOAL_MANAGER_HXX
#define HEADER_GOAL_MANAGER_HXX

/** The GoalManager keeps track of game events such as a soldier
    entering a vehicle, a specific vehicle getting destroyed und stuff
    like that. Other parts of the engine can make use of this
    information to manage primary/secondary missions goals.
 */
class GoalManager
{
private:
public:
  // FIXME: Design me
  GoalManager() {}
private:
  GoalManager (const GoalManager&);
  GoalManager& operator= (const GoalManager&);
};

#endif

/* EOF */
