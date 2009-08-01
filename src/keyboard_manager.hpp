//  $Id: keyboard_manager.hpp,v 1.6 2003/10/31 23:24:41 grumbel Exp $
// 
//  Feuerkraft - A Tank Battle Game
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

#ifndef HEADER_KEYBOARD_MANAGER_HXX
#define HEADER_KEYBOARD_MANAGER_HXX

#include <vector>
#include <ClanLib/Display/input_event.h>

/** Management class for keyboard events, if a key is pressed it looks
    up a callback and if one it set it evalutes the callback. This
    class is mainly used for user-created callback functions from
    Guile */
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
  std::vector<CL_Slot> slots;

  struct Callback {
    int key_id;
    Callback(int id)
      : key_id(id)
    {}

    virtual void run() =0;
  };
  
  template<class C>
  struct GenericCallback
    : public Callback {
    C callback;
    GenericCallback(int key_id, const C& c) 
      : Callback(key_id), 
        callback(c)
    {
    }

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
private:
  void button_up(const CL_InputEvent& event);
  void button_down(const CL_InputEvent& event);

  KeyboardManager (const KeyboardManager&);
  KeyboardManager& operator= (const KeyboardManager&);
};

#endif

/* EOF */
