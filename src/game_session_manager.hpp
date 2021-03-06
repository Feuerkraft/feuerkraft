// Feuerkraft - A Tank Battle Game
// Copyright (C) 2002 Ingo Ruhnke <grumbel@gmail.com>
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

#ifndef HEADER_GAME_SESSION_MANAGER_HXX
#define HEADER_GAME_SESSION_MANAGER_HXX

#include <string>

class GameSession;

/** */
class GameSessionManager
{
private:
  static GameSessionManager* instance_;
public:
  static GameSessionManager* instance();

private:
  bool session_changed;
  bool do_quit;
  GameSession* current_session;
  GameSession* new_session;
public:
  GameSessionManager();
  ~GameSessionManager();

  void load(const std::string& filename);
  void save(const std::string& filename);

  void run();
  void pause();
  void quit();

private:
  GameSessionManager (const GameSessionManager&);
  GameSessionManager& operator= (const GameSessionManager&);
};

#endif

/* EOF */
