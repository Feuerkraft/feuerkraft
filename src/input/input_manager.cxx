//  $Id: input_manager.cxx,v 1.2 2003/06/06 18:18:13 grumbel Exp $
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

#include "input_manager_clanlib.hxx"
#include "input_manager_impl.hxx"
#include "input_manager.hxx"

InputManagerImpl* InputManager::impl = 0;

void
InputManager::init(InputManagerImpl* arg_impl)
{
  if (arg_impl)
    impl = arg_impl;
  else
    impl = new InputManagerClanLib();
}

void 
InputManager::deinit()
{
  delete impl;
}

void
InputManager::update(float delta)
{
  assert(impl);
  impl->update(delta);
}

InputEventLst
InputManager::get_events()
{
  assert(impl);
  return impl->get_events();
}

Controller
InputManager::get_controller()
{
  assert(impl);
  return impl->get_controller();
}

/* EOF */
