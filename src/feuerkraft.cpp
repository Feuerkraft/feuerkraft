// Feuerkraft - A Tank Battle Game
// Copyright (C) 2000 Ingo Ruhnke <grumbel@gmail.com>
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

#include <config.h>
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <libguile.h>
#include <ctime>

#include "system.hpp"
#include "display.hpp"

#include "feuerkraft_error.hpp"
#include "fonts.hpp"
#include "input/game_controllers.hpp"
#include "input/input_manager.hpp"
#include "game_session_manager.hpp"
#include "keyboard_manager.hpp"
#include "resource_manager.hpp"
#include "path_manager.hpp"
#include "globals.hpp"
#include "sound/sound.hpp"
#include "command_line_arguments.hpp"
#include "guile.hpp"
#include "feuerkraft.hpp"

//#define WITH_STATIC_READLINE 1

#ifdef WITH_STATIC_READLINE
extern "C" void scm_init_readline();
#endif
extern "C" void SWIG_init(void);


// Global Instance of the main class
Feuerkraft feuerkraft;
CommandLineArguments* args;

Feuerkraft::Feuerkraft() :
  window(nullptr)
{
  args = 0;
}

Feuerkraft::~Feuerkraft()
{
  delete args;
}

void
Feuerkraft::init()
{
  // Init Guile
  scm_init_guile ();
  Guile::enable_debug();
  Guile::enable_readline();

  // Init Swig
  SWIG_init();

  // Init SDL2
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) < 0)
    {
      throw FeuerkraftError(std::string("SDL_Init failed: ") + SDL_GetError());
    }
  if (!(IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) & (IMG_INIT_PNG | IMG_INIT_JPG)))
    {
      throw FeuerkraftError(std::string("IMG_Init failed: ") + IMG_GetError());
    }

  // Init Sound Subsystem
  music_enabled = args->music_enabled;
  sound_enabled = args->sound_enabled;
  PingusSound::init();

  // Init pseudo random number generator
  srand (time (0));

  // Find the location of Feuerkraft data files (images, sounds, etc.)
  // Prefer --datadir, then the compile-time FEUERKRAFT_DATADIR, then
  // paths relative to the executable (developer builds).
  if (!args->datadir.empty())
    {
      path_manager.add_path(args->datadir);
    }
  else
    {
#ifdef FEUERKRAFT_DATADIR
      path_manager.add_path(FEUERKRAFT_DATADIR);
#endif
      std::string exe_path = System::get_exe_path();
      path_manager.add_path(exe_path + "../data");
      path_manager.add_path(exe_path + "data");
      path_manager.add_path(exe_path + "share/feuerkraft");
      path_manager.add_path(exe_path + "share/games/feuerkraft");
      path_manager.add_path(exe_path + "../share/feuerkraft");
      path_manager.add_path(exe_path + "../share/games/feuerkraft");
    }
  if (!path_manager.find_path("feuerkraft.xml"))
    {
      throw FeuerkraftError(
        "Could not find data directory (feuerkraft.xml). "
        "Pass --datadir or install data to FEUERKRAFT_DATADIR.");
    }

  // Create the main window (SDL2) — full graphics port follows in later phases
  Uint32 flags = SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE;
  if (args->fullscreen)
    flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
  window = SDL_CreateWindow(PACKAGE_STRING,
                            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                            args->screen_width, args->screen_height,
                            flags);
  if (!window)
    {
      throw FeuerkraftError(std::string("SDL_CreateWindow failed: ") + SDL_GetError());
    }

  // Prefer linear filtering for scaled sprites/light cones (ClanLib default)
  SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

  SDL_Renderer* renderer = SDL_CreateRenderer(window, -1,
                                              SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (!renderer)
    {
      // Fall back to software renderer
      renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    }
  if (!renderer)
    {
      throw FeuerkraftError(std::string("SDL_CreateRenderer failed: ") + SDL_GetError());
    }

  // Logical resolution = window size / scale so that --size WxH --scale S
  // yields the same viewable area as --size (W/S)x(H/S) --scale 1, with
  // bigger pixels when S > 1.
  int logical_w = args->screen_width / args->scale;
  int logical_h = args->screen_height / args->scale;
  if (logical_w < 1) logical_w = 1;
  if (logical_h < 1) logical_h = 1;
  SDL_RenderSetLogicalSize(renderer, logical_w, logical_h);

  Display::init(window, renderer);
  Display::clear();

  resources = new ResourceManager ();
  Fonts::init();

  KeyboardManager::instance();

  if (args->playback_file.empty())
    {
      if (args->controller_file.empty())
        {
          InputManager::init(path_manager.complete("controller/keyboard.scm"));
        }
      else
        {
          InputManager::init(args->controller_file);
        }
    }
  else
    {
      InputManager::init_playback(args->playback_file);
    }

  if (!args->event_record_file.empty())
    InputManager::setup_recorder(args->event_record_file);
}

void
Feuerkraft::deinit()
{
  Fonts::deinit();
  GameControllers::clear();
  PingusSound::deinit();

  SDL_Renderer* renderer = Display::get_renderer();
  Display::deinit();
  if (renderer)
    SDL_DestroyRenderer(renderer);
  if (window)
    {
      SDL_DestroyWindow(window);
      window = nullptr;
    }
  IMG_Quit();
  SDL_Quit();
}

int
Feuerkraft::main(int argc, char** argv)
{
  try
    {
      // Make arguments accessible for all member functions
      args = new CommandLineArguments(argc, argv);

      // Init all subsystems
      init();

      if (args->mission_file.empty())
        args->mission_file = path_manager.complete("missions/airport.feu");

      // Keyboard handling will be ported to SDL events in Phase 4
      GameSessionManager::instance()->load(args->mission_file);
      GameSessionManager::instance()->run();

      // Shutdown everything
      deinit();
    }
  catch (FeuerkraftError& err)
    {
      std::cout << "FeuerkraftError: " << err.what() << std::endl;
    }
  catch (std::exception& err)
    {
      std::cout << "Error: " << err.what() << std::endl;
    }
  catch (...)
    {
      std::cout << "Bug: Unknown exception catched, don't know what to do" << std::endl;
    }

  return 0;
}

// key_down removed; will be replaced by SDL event handling

int main(int argc, char** argv)
{
  return feuerkraft.main(argc, argv);
}

// EOF //

