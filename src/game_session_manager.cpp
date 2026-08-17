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

#include <iostream>
#include "path_manager.hpp"
#include "system.hpp"
#include "command_line_arguments.hpp"
#include "game_session.hpp"
#include "game_session_manager.hpp"
#include "log.hpp"

GameSessionManager* GameSessionManager::instance_ = 0;

GameSessionManager*
GameSessionManager::instance()
{
  if (instance_)
    return instance_;
  else
    return (instance_ = new GameSessionManager());
}

GameSessionManager::GameSessionManager()
  : session_changed(false),
    session_active(false),
    do_quit(false),
    current_session(0),
    new_session(0)
{
}

GameSessionManager::~GameSessionManager()
{
  if (session_active && current_session)
    current_session->deinit();
  delete current_session;
  delete new_session;
}

void
GameSessionManager::load(const std::string& filename)
{
  if (!current_session)
    {
      current_session = new GameSession(filename);
    }
  else
    {
      new_session     = new GameSession(path_manager.complete(filename));
      session_changed = true;
    }
}

void
GameSessionManager::save(const std::string& filename)
{
  std::cout << "### Saving game to '" << filename << "' not implemented" << std::endl;
  current_session->save(filename);
}

bool
GameSessionManager::tick()
{
  if (do_quit)
    return false;

  // Apply a pending session switch before advancing a frame.
  if (session_changed)
    {
      if (session_active && current_session)
        {
          current_session->deinit();
          session_active = false;
        }
      delete current_session;
      current_session = new_session;
      new_session = 0;
      session_changed = false;
    }

  if (!current_session)
    {
      fk_log_error("GameSessionManager: no session — quitting");
      do_quit = true;
      return false;
    }

  if (!session_active)
    {
      fk_log("GameSession::init() begin");
      current_session->init();
      session_active = true;
      fk_log("GameSession::init() done");
    }

  current_session->update();

  return !do_quit;
}

void
GameSessionManager::run()
{
  // Native blocking loop. Under WASM, call tick() from the host frame
  // callback instead (e.g. emscripten_set_main_loop).
  fk_log("GameSessionManager::run() loop start");
  while (tick())
    {
      // Frame pacing is the responsibility of the native runner only.
      // GameSession::update() no longer sleeps, so WASM hosts that drive
      // tick() via requestAnimationFrame are not blocked.
      if (args && args->fps > 0.0f)
        {
          // Approximate fixed-timestep sleep; fine for desktop.
          // A more precise approach would measure elapsed time, but the
          // previous code used the same simple limit.
          const int delta_wait = static_cast<int>(1000.0f / args->fps);
          if (delta_wait > 0)
            System::sleep(static_cast<unsigned int>(delta_wait));
        }
    }

  if (session_active && current_session)
    {
      current_session->deinit();
      session_active = false;
    }
}

void
GameSessionManager::pause()
{
  if (current_session)
    current_session->pause();
}

void
GameSessionManager::quit()
{
  do_quit = true;
}

/* EOF */
