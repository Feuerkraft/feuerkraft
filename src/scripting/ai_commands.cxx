//  $Id: ai_commands.cxx,v 1.2 2003/06/18 14:38:28 grumbel Exp $
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

#include "../soldier.hxx"
#include "script_helper.hxx"
#include "../ai_manager.hxx"
#include "ai_commands.hxx"

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

/* EOF */
