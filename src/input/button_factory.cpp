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

#include <SDL.h>
#include <map>
#include <string>
#include "../guile.hpp"
#include "../feuerkraft_error.hpp"
#include "input_button.hpp"
#include "input_axis.hpp"
#include "input_button_input_device.hpp"
#include "axis_factory.hpp"
#include "axis_button.hpp"
#include "multi_button.hpp"
#include "button_factory.hpp"
#include "input_button_game_controller.hpp"
#include "game_controllers.hpp"

namespace {

SDL_Scancode
name_to_scancode(const std::string& name)
{
  // Common keys used in the controller .scm files
  static const std::map<std::string, SDL_Scancode> table = {
    {"escape", SDL_SCANCODE_ESCAPE},
    {"return", SDL_SCANCODE_RETURN},
    {"enter", SDL_SCANCODE_RETURN},
    {"space", SDL_SCANCODE_SPACE},
    {"left", SDL_SCANCODE_LEFT},
    {"right", SDL_SCANCODE_RIGHT},
    {"up", SDL_SCANCODE_UP},
    {"down", SDL_SCANCODE_DOWN},
    {"a", SDL_SCANCODE_A}, {"b", SDL_SCANCODE_B}, {"c", SDL_SCANCODE_C},
    {"d", SDL_SCANCODE_D}, {"e", SDL_SCANCODE_E}, {"f", SDL_SCANCODE_F},
    {"g", SDL_SCANCODE_G}, {"h", SDL_SCANCODE_H}, {"i", SDL_SCANCODE_I},
    {"j", SDL_SCANCODE_J}, {"k", SDL_SCANCODE_K}, {"l", SDL_SCANCODE_L},
    {"m", SDL_SCANCODE_M}, {"n", SDL_SCANCODE_N}, {"o", SDL_SCANCODE_O},
    {"p", SDL_SCANCODE_P}, {"q", SDL_SCANCODE_Q}, {"r", SDL_SCANCODE_R},
    {"s", SDL_SCANCODE_S}, {"t", SDL_SCANCODE_T}, {"u", SDL_SCANCODE_U},
    {"v", SDL_SCANCODE_V}, {"w", SDL_SCANCODE_W}, {"x", SDL_SCANCODE_X},
    {"y", SDL_SCANCODE_Y}, {"z", SDL_SCANCODE_Z},
    {"keypad 0", SDL_SCANCODE_KP_0}, {"keypad 1", SDL_SCANCODE_KP_1},
    {"keypad 2", SDL_SCANCODE_KP_2}, {"keypad 3", SDL_SCANCODE_KP_3},
    {"keypad 4", SDL_SCANCODE_KP_4}, {"keypad 5", SDL_SCANCODE_KP_5},
    {"keypad 6", SDL_SCANCODE_KP_6}, {"keypad 7", SDL_SCANCODE_KP_7},
    {"keypad 8", SDL_SCANCODE_KP_8}, {"keypad 9", SDL_SCANCODE_KP_9},
    {"f1", SDL_SCANCODE_F1}, {"f2", SDL_SCANCODE_F2}, {"f3", SDL_SCANCODE_F3},
    {"f4", SDL_SCANCODE_F4}, {"f5", SDL_SCANCODE_F5}, {"f6", SDL_SCANCODE_F6},
    {"f7", SDL_SCANCODE_F7}, {"f8", SDL_SCANCODE_F8}, {"f9", SDL_SCANCODE_F9},
    {"f10", SDL_SCANCODE_F10}, {"f11", SDL_SCANCODE_F11}, {"f12", SDL_SCANCODE_F12},
  };

  auto it = table.find(name);
  if (it != table.end())
    return it->second;

  // Fallback: try SDL's own name resolver
  SDL_Scancode sc = SDL_GetScancodeFromName(name.c_str());
  if (sc != SDL_SCANCODE_UNKNOWN)
    return sc;

  return SDL_SCANCODE_UNKNOWN;
}

} // namespace

InputButton*
ButtonFactory::create(SCM lst)
{
  SCM sym = scm_car(lst);

  if (Guile::equal_p(sym, scm_from_utf8_symbol("joystick-button")))
    return create_joystick_button(scm_cdr(lst));
  else if (Guile::equal_p(sym, scm_from_utf8_symbol("keyboard-button")))
    return create_keyboard_button(scm_cdr(lst));
  else if (Guile::equal_p(sym, scm_from_utf8_symbol("axis-button")))
    return create_axis_button(scm_cdr(lst));
  else if (Guile::equal_p(sym, scm_from_utf8_symbol("multi-button")))
    return create_multi_button(scm_cdr(lst));
  else
    feuerkraft_fatal("ButtonFactory::create: parse error: '"
                          + Guile::scm2string(lst) + "'");
  return 0;
}

InputButton*
ButtonFactory::create_axis_button(SCM lst)
{
  InputAxis* axis = AxisFactory::create(scm_car(lst));
  bool top = scm_to_bool(scm_cadr(lst));
  return new AxisButton(axis, top);
}

InputButton*
ButtonFactory::create_joystick_button(SCM lst)
{
  // (joystick-button device button) → SDL_GameController button
  // button: 0=A 1=B 2=X 3=Y 4=BACK 5=GUIDE 6=START 7=LEFTSTICK
  //         8=RIGHTSTICK 9=LEFTSHOULDER 10=RIGHTSHOULDER 11=DPAD_UP …
  int device_num = scm_to_int(scm_car(lst));
  int button_num = scm_to_int(scm_cadr(lst));
  SDL_GameController* gc = GameControllers::get(device_num);
  return new InputButtonGameController(gc, button_num);
}

InputButton*
ButtonFactory::create_keyboard_button(SCM lst)
{
  std::string key_str = Guile::scm2string(scm_car(lst));
  SDL_Scancode sc = name_to_scancode(key_str);
  return new InputButtonInputDevice(sc);
}

InputButton*
ButtonFactory::create_multi_button(SCM lst)
{
  MultiButton* button = new MultiButton();
  while (!scm_is_true(scm_null_p(lst)))
    {
      button->add(create(scm_car(lst)));
      lst = scm_cdr(lst);
    }
  return button;
}

/* EOF */
