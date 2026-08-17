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

/**
 * Owns the active GameSession and advances it one frame at a time.
 *
 * The blocking main loop lives in run(). For environments that cannot
 * block (e.g. WebAssembly / Emscripten), call tick() repeatedly from an
 * external frame callback instead of run().
 */
class GameSessionManager
{
private:
  static GameSessionManager* instance_;
public:
  static GameSessionManager* instance();

private:
  bool session_changed;
  bool session_active;   /**< true while current_session has been init()'d */
  bool do_quit;
  GameSession* current_session;
  GameSession* new_session;
public:
  GameSessionManager();
  ~GameSessionManager();

  void load(const std::string& filename);
  void save(const std::string& filename);

  /**
   * Advance the game by a single frame.
   * @return false when the application should exit (quit requested).
   *
   * Safe to call from an Emscripten main-loop callback or similar.
   * Does not sleep; the caller is responsible for frame pacing if needed.
   */
  bool tick();

  /**
   * Native blocking main loop: repeatedly calls tick() and sleeps to
   * honour the configured FPS limit until quit is requested.
   * Do not use under WASM — drive tick() from the host event loop instead.
   */
  void run();

  void pause();
  void quit();

  bool should_quit() const { return do_quit; }

private:
  GameSessionManager (const GameSessionManager&);
  GameSessionManager& operator= (const GameSessionManager&);
};

#endif

/* EOF */
