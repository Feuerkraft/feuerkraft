//  $Id: game_session.hpp,v 1.1 2003/06/18 13:04:21 grumbel Exp $
// 
//  Pingus - A free Lemmings clone
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

#ifndef HEADER_GAME_SESSION_HXX
#define HEADER_GAME_SESSION_HXX

#include <string>

class BuildingTypeManager;
class CollisionManager;
class GameWorld;
class View;

/** */
class GameSession
{
private:
  enum ControlState { UNIT_CONTROL, MENU_CONTROL } control_state; 

  std::string filename;
  bool  do_quit;
  bool  do_pause;
  float deltas;
  int   loops;
  int   frames;
  int   start_time;

  BuildingTypeManager* buildingtypemanager;
  CollisionManager*    collision_mgr;
  GameWorld* world;
  View*      view;

public:
  GameSession(const std::string& arg_filename);
  
  void init();
  void deinit();

  /** Run a GameSession, quit when some end condition occures */
  void update();

  void pause();

  void save(const std::string& arg_filename);
private:
  GameSession (const GameSession&);
  GameSession& operator= (const GameSession&);
};

#endif

/* EOF */
