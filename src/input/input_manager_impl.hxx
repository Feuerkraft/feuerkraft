//  $Id: input_manager_impl.hxx,v 1.1 2003/06/04 10:59:00 grumbel Exp $
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

#ifndef HEADER_INPUT_MANAGER_IMPL_HXX
#define HEADER_INPUT_MANAGER_IMPL_HXX

#include "input_event.hxx"

/** */
class InputManagerImpl
{
public:
  InputManagerImpl() {}
  virtual void update(float delta) =0;
  virtual InputEventLst get_events() =0;
private:
  InputManagerImpl(const InputManagerImpl&);
  InputManagerImpl& operator=(const InputManagerImpl&);
};

#endif

/* EOF */
