//  $Id: trigger_manager.cxx,v 1.1 2003/05/02 16:20:45 grumbel Exp $
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

#include <iostream>
#include <algorithm>
#include "trigger_manager.hxx"

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
