//  $Id: trigger_manager.cpp,v 1.2 2003/06/03 14:11:22 grumbel Exp $
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

#include <iostream>
#include <algorithm>
#include "trigger_manager.hpp"

TriggerManager* TriggerManager::current_ = 0;

TriggerManager::TriggerManager()
{
  current_ = this;
}

struct TriggerIsRemovable
{
  bool operator()(TriggerManager::Trigger* trigger) {
    return trigger->removable;
  }
};

void
TriggerManager::update(float delta)
{
  // Keep iterators intact
  Triggers tmp_triggers = triggers;
  for (Triggers::iterator i = tmp_triggers.begin(); i != tmp_triggers.end(); ++i)
    {
      (*i)->update(delta);
    }

  triggers.erase(std::remove_if(triggers.begin(), triggers.end (), TriggerIsRemovable()),
                 triggers.end ());
}

/* EOF */
