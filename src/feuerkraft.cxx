//  $Id: feuerkraft.cxx,v 1.55 2003/10/31 23:24:41 grumbel Exp $
// 
//  Feuerkraft - A Tank Battle Game
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

#include <config.h>
#include <iostream>
#include <ClanLib/gl.h>
#include <ClanLib/Display/setupdisplay.h>
#include <ClanLib/Display/display.h>
#include <ClanLib/GL/setupgl.h>
#include <ClanLib/core.h>
#include <libguile.h>
#include <time.h>

#include "feuerkraft_error.hxx"
#include "fonts.hxx"
#include "input/input_manager.hxx"
#include "game_session_manager.hxx"
#include "keyboard_manager.hxx"
#include "resource_manager.hxx"
#include "path_manager.hxx"
#include "globals.hxx"
#include "sound/sound.hxx"
#include "command_line_arguments.hxx"
#include "guile.hxx"
#include "feuerkraft.hxx"

//#define WITH_STATIC_READLINE 1

#ifdef WITH_STATIC_READLINE
extern "C" void scm_init_readline();
#endif
extern "C" void SWIG_init(void);
          

// Global Instance of the main class
Feuerkraft feuerkraft;
CommandLineArguments* args;

Feuerkraft::Feuerkraft()
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

  // Init ClanLib
  CL_SetupCore::init();
  CL_SetupDisplay::init();
  CL_SetupGL::init();

  // Init Sound Subsystem
  music_enabled = args->music_enabled;
  sound_enabled = args->sound_enabled;
  PingusSound::init();

  // Init pseudo random number generator
  srand (time (0));

  // Find the location of Feuerkrafts data files (images, sounds, etc.) 
  if (!args->datadir.empty())
    {
    }
  else
    {
      path_manager.add_path(CL_System::get_exe_path() + "../data");
      path_manager.add_path("../data");
      path_manager.add_path("data");
      path_manager.add_path("share/games/feuerkraft");
      path_manager.add_path("../share/games/feuerkraft");
      path_manager.find_path("feuerkraft.xml");     
    }

  // Create the main window
  window = new CL_DisplayWindow(PACKAGE_STRING,
                                args->screen_width, args->screen_height, 
                                args->fullscreen);
  CL_Display::set_current_window (window);
  CL_Display::clear();

  resources = new ResourceManager ();
  Fonts::init();

  KeyboardManager::instance();

  if (args->playback_file.empty())
    {
      if (args->controller_file.empty())
        {
          InputManager::init(path_manager.complete("controller.scm"));
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
  PingusSound::deinit();
  CL_SetupGL::deinit();
  CL_SetupDisplay::deinit();
  CL_SetupCore::deinit();
}
	
int
Feuerkraft::main(int argc, char** argv)
{
  // Create a console window for text-output if not available
  CL_ConsoleWindow console("Console");
  console.redirect_stdio();
  
  try
    {
      // Make arguments accessible for all member functions
      args = new CommandLineArguments(argc, argv);

      // Init all subsystems
      init();
      
      if (args->mission_file.empty())
        args->mission_file = path_manager.complete("missions/airport.feu");

      GameSessionManager::instance()->load(args->mission_file);
      GameSessionManager::instance()->run();

      // Shutdown everything
      deinit();
    }
  catch (CL_Error& err)
    {
      std::cout << "CL_Error: " << err.message.c_str() << std::endl;
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

  // Display console close message and wait for a key
  console.display_close_message();

  return 0;
}

// EOF //
