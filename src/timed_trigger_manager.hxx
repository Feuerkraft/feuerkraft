//  $Id: timed_trigger_manager.hxx,v 1.1 2003/05/02 14:28:26 grumbel Exp $
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

#ifndef HEADER_TIMED_TRIGGER_MANAGER_HXX
#define HEADER_TIMED_TRIGGER_MANAGER_HXX

#include <vector>

/** */
class TimedTriggerManager
{
private:
  static TimedTriggerManager* current_;
public:
  static TimedTriggerManager* current() { return current_; }

public:
  struct TimedTrigger {
    bool removable;
    float seconds;
    TimedTrigger(float arg_seconds)
      : removable(false),
        seconds(arg_seconds) 
    {
    }
    
    void update(float delta) {
      seconds -= delta;
      if (seconds < 0)
        {
          call();
          removable = true;
        }
    }

    virtual void call() =0;
  };

  template<class Func>
  struct GenericTimedTrigger : public TimedTrigger {
    Func func;

    GenericTimedTrigger(float seconds, Func arg_func)
      : TimedTrigger(seconds),
        func(arg_func)
    {
    }

    virtual ~GenericTimedTrigger() {}

    void call() { func(); }
  };

  typedef std::vector<TimedTrigger*> Triggers;
private:
  Triggers triggers;
public:
  TimedTriggerManager();

  void update(float delta);

  template<class Func>
  void add_trigger(float seconds, Func func) {
    triggers.push_back(new GenericTimedTrigger<Func>(seconds, func));
  }
private:
  TimedTriggerManager (const TimedTriggerManager&);
  TimedTriggerManager& operator= (const TimedTriggerManager&);
};

#endif

/* EOF */
