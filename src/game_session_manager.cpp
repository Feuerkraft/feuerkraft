//  $Id: game_session_manager.cxx,v 1.1 2003/06/10 00:38:50 grumbel Exp $
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

#include <iostream>
#include "path_manager.hxx"
#include "game_session.hxx"
#include "game_session_manager.hxx"

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
    do_quit(false),
    current_session(0),
    new_session(0)
{
}

GameSessionManager::~GameSessionManager()
{
  delete current_session;
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

void
GameSessionManager::run()
{
  while(!do_quit)
    {
      current_session->init();

      while(!do_quit && !session_changed)
        current_session->update();

      current_session->deinit();

      if (session_changed)
        {
          delete current_session;
          current_session = new_session;
          session_changed = false;
        }
    }
}

void
GameSessionManager::pause()
{
  current_session->pause();
}

void
GameSessionManager::quit()
{
  do_quit = true;
}

/* EOF */
