//  $Id: keyboard_manager.hxx,v 1.4 2003/06/03 14:11:22 grumbel Exp $
// 
//  Feuerkraft - A Tank Battle Game
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

#ifndef HEADER_KEYBOARD_MANAGER_HXX
#define HEADER_KEYBOARD_MANAGER_HXX

#include <vector>
#include <ClanLib/Display/input_event.h>

/** Management class for keyboard events, if a key is pressed it looks
    up a callback and if one it set it evalutes the callback */
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
  CL_Slot keyboard_button_up_slot;
  CL_Slot keyboard_button_down_slot;
  CL_Slot mouse_button_up_slot;
  CL_Slot mouse_button_down_slot;

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
