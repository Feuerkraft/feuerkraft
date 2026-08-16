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

#ifndef HEADER_KEYBOARD_MANAGER_HXX
#define HEADER_KEYBOARD_MANAGER_HXX

#include <vector>
#include <SDL.h>
#include "signal.hpp"

/** Management class for keyboard events. During the SDL2 port the
    low-level ClanLib input is replaced; callbacks are still supported
    and will be driven from the main SDL event loop. */
class KeyboardManager
{
private:
  static KeyboardManager* instance_;
public:
  static KeyboardManager* instance() {
    if (instance_)
      return instance_;
    else
      return instance_ = new KeyboardManager();
  }
private:
  struct Callback {
    int key_id;
    Callback(int id) : key_id(id) {}
    virtual ~Callback() {}
    virtual void run() =0;
  };

  template<class C>
  struct GenericCallback : public Callback {
    C callback;
    GenericCallback(int key_id, const C& c)
      : Callback(key_id), callback(c) {}
    virtual ~GenericCallback() {}
    void run() { callback(); }
  };

  typedef std::vector<Callback*> Callbacks;
  Callbacks callbacks;

public:
  KeyboardManager();
  ~KeyboardManager();

  template<class C>
  void register_down_callback(int key_id, const C& c) {
    callbacks.push_back(new GenericCallback<C>(key_id, c));
  }

  /** Called from the main loop with SDL keyboard events. */
  void on_key_down(int key_id);
  void on_key_up(int key_id);

private:
  KeyboardManager (const KeyboardManager&);
  KeyboardManager& operator= (const KeyboardManager&);
};

#endif

/* EOF */
