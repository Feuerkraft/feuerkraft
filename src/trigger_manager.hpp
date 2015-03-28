// Feuerkraft - A Tank Battle Game
// Copyright (C) 2002 Ingo Ruhnke <grumbel@gmx.de>
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

#ifndef HEADER_TRIGGER_MANAGER_HXX
#define HEADER_TRIGGER_MANAGER_HXX

#include <iostream>
#include <vector>
#include "unit.hpp"
#include "game_world.hpp"
#include "player.hpp"
#include "game_obj_manager.hpp"

extern Player* player;

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
          this->func();
          this->remove();
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

    void update(float delta)
    {
      Unit* unit = player->get_current_unit();

      if (unit)
        {
          if (int(unit->get_pos().x/40) == x && int(unit->get_pos().y/40) == y)
            {
              this->func(SCM_MAKINUM(unit->get_id()));
              this->remove();
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
