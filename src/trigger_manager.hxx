//  $Id: trigger_manager.hxx,v 1.2 2003/06/03 14:11:22 grumbel Exp $
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

#ifndef HEADER_TRIGGER_MANAGER_HXX
#define HEADER_TRIGGER_MANAGER_HXX

#include <vector>
#include "vehicle.hxx"
#include "game_world.hxx"
#include "game_obj_manager.hxx"

/** */
class TriggerManager
{
private:
  static TriggerManager* current_;
public:
  static TriggerManager* current() { return current_; }

public:
  struct Trigger {
    bool removable;
    
    Trigger() : removable(false) {}
    void remove() { removable = true; }
    virtual void update(float delta) =0;
  };

  template<class Func>
  struct FunctorTrigger : public Trigger {
    Func func;

    FunctorTrigger(Func arg_func) : func(arg_func) {}
    virtual ~FunctorTrigger() {}

    virtual void update(float delta) =0;
  }; // struct Trigger

  template<class Func>
  struct TimedTrigger : public FunctorTrigger<Func> {
    float seconds;

    TimedTrigger(float arg_seconds, Func arg_func)
      : FunctorTrigger<Func>(arg_func),
        seconds(arg_seconds){}

    virtual ~TimedTrigger() {}

    void update(float delta) {
      seconds -= delta;
      if (seconds < 0)
        {
          func();
          remove();
        }
    }
  };// struct TimedTrigger

  template<class Func>
  struct TileTrigger : public FunctorTrigger<Func> {
    int x;
    int y;

    TileTrigger(int arg_x, int arg_y, Func arg_func)
      : FunctorTrigger<Func>(arg_func),
        x(arg_x), y(arg_y)
    {
    }

    virtual ~TileTrigger() {}

    void update(float delta) {
      GameObjManager* objs = GameWorld::current()->get_game_obj_manager();
      for (GameObjManager::iterator i = objs->begin(); i != objs->end(); ++i)
        {
          Vehicle* vehicle = dynamic_cast<Vehicle*>(*i);
          if (vehicle)
            {
              if (int(vehicle->get_pos().x/40) == x
                  && int(vehicle->get_pos().y/40) == y)
                {
                  func(SCM_MAKINUM(vehicle->get_id()));
                  remove();
                }
            }
        }
    }
  };// struct TileTrigger

  typedef std::vector<Trigger*> Triggers;
private:
  Triggers triggers;
public:
  TriggerManager();

  void update(float delta);

  template<class Func>
  void add_timed_trigger(float seconds, Func func) {
    triggers.push_back(new TimedTrigger<Func>(seconds, func));
  }

  template<class Func>
  void add_tile_trigger(int x, int y, Func func) {
    triggers.push_back(new TileTrigger<Func>(x, y, func));
  }
private:
  TriggerManager (const TriggerManager&);
  TriggerManager& operator= (const TriggerManager&);
};

#endif

/* EOF */
