//  $Id: ai_commands.cpp,v 1.3 2003/06/20 20:54:23 grumbel Exp $
//
//  Pingus - A free Lemmings clone
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

#include "../soldier.hpp"
#include "../ai_manager.hpp"
#include "script_helper.hpp"
#include "ai_commands.hpp"

void
ai_goto(int handle, float x, float y)
{
  Soldier* soldier = Scripting::get_object<Soldier>(handle);

  if (soldier)
    {
      AI* ai = AIManager::instance()->get_ai(soldier);
      SoldierAI* soldier_ai = 0;
      if (ai && (soldier_ai = dynamic_cast<SoldierAI*>(ai)))
        {
          soldier_ai->goto_to(FloatVector2d(x, y));
        }
      else
        {
          std::cout << "Soldier doesn't have an AI" << std::endl;
        }
    }
  else
    {
      std::cout << "No soldier with id: " << handle << std::endl;
    }
}

void
ai_stop(int handle)
{
  SoldierAI* soldier_ai = Scripting::get_ai<SoldierAI>(handle);
  if (soldier_ai)
    soldier_ai->stop();
}

bool
ai_has(int handle)
{
  AI* ai = AIManager::instance()->get_ai(Scripting::get_object<GameObj>(handle));
  return ai;
}

void
ai_attach(int handle)
{
  Unit* unit = Scripting::get_object<Unit>(handle);
  if (unit)
    unit->attach_ai();
}

void ai_dettach(int handle)
{
  Unit* unit = Scripting::get_object<Unit>(handle);
  if (unit)
    unit->dettach_ai();
}

/* EOF */
