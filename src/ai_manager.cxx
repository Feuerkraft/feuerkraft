//  $Id: ai_manager.cxx,v 1.1 2003/06/18 00:27:09 grumbel Exp $
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

#include "ai.hxx"
#include "ai_manager.hxx"

AIManager* AIManager::instance_ = 0;

AIManager*
AIManager::instance()
{
  if (instance_)
    return instance_;
  else
    return instance_ = new AIManager();
}

void
AIManager::add(AI* ai)
{
  ais.push_back(ai);
}

void
AIManager::update(float delta)
{
  for (std::vector<AI*>::iterator i = ais.begin(); i != ais.end(); ++i)
    {
      (*i)->update(delta);
    }
}

/* EOF */
