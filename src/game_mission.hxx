//  $Id: game_mission.hxx,v 1.2 2003/05/02 14:28:26 grumbel Exp $
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

#ifndef GAMEMISSION_HXX
#define GAMEMISSION_HXX

#include <string>
#include <libguile.h>

class GameWorld;

/** The GameMission class holds all the data which is relevant for a
    mission. Which means it will hold the GameWorld data, briefing
    data, mission description, scripts and meta-data such as creation
    time, author, email, etc. */
// FIXME: Data -> GameObj seperation not here!
class GameMission
{
private:
  std::string author_name;
  std::string author_email;
  unsigned int creation_time;
  GameWorld* world;
  
public:
  /** Create an GameMission out of an SCM description. A game mission
      is stored in a directory with the files [FIXME:...] */
  GameMission (SCM desc);
  virtual ~GameMission ();

  /** Return the date of the mission creation in number of seconds
      since 1. Jan 1970 (standard unix time) */
  unsigned int get_creation_time ();
  
  // FIXME: What about support for multiple authors? -> useless?!

  /** Return the authors name */
  std::string get_author_name ();

  /** Return the authors email address */
  std::string get_author_email ();

  /** Return a pointer to the GameWorld for this mission !!! FIXME:
      how do we handle multiple GameWorld's in a single mission? */
  GameWorld*  get_world ();
};

#endif

/* EOF */
