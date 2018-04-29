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
#include <assert.h>
#include <stdexcept>
#include <sstream>
#include <ClanLib/Display/joystick.h>

#include "../feuerkraft_error.hpp"
#include "input_manager_custom.hpp"
#include "input_manager_player.hpp"
#include "input_manager_impl.hpp"
#include "input_recorder.hpp"
#include "input_manager.hpp"
#include "guile.hpp"

InputManagerImpl* InputManager::impl = 0;
InputRecorder* InputManager::recorder = 0;

void
InputManager::init_playback(const std::string& filename)
{
  impl = new InputManagerPlayer(filename);
}

void
InputManager::init(const std::string& filename)
{
  std::cout << "InputManager::init(" << filename << ")" << std::endl;
  SCM port = scm_open_file(scm_from_utf8_string(filename.c_str()),
                           scm_from_utf8_string("r"));
  SCM lst  = scm_read(port);

  if (Guile::equal_p(scm_from_utf8_symbol("feuerkraft-controller"), scm_car(lst)))
    {
      impl = new InputManagerCustom(scm_cdr(lst));
    }
  else
    {
      throw FeuerkraftError("Error: not a valid controller file: " + filename);
    }
  scm_close_port(port);
}

void
InputManager::setup_recorder(const std::string& filename)
{
  if (recorder)
    delete recorder;

  recorder = new InputRecorder(filename);
}

void
InputManager::deinit()
{
  delete impl;
}

void
InputManager::update(float delta)
{
  assert(impl);
  impl->update(delta);
  if (recorder)
    recorder->record(get_controller());
}

Controller
InputManager::get_controller()
{
  assert(impl);
  return impl->get_controller();
}

void
InputManager::clear()
{
  impl->clear();
}

/* EOF */
