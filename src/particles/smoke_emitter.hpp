//  $Id: smoke_emitter.hpp,v 1.1 2003/06/07 17:19:19 grumbel Exp $
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

#ifndef HEADER_SMOKE_EMITTER_HXX
#define HEADER_SMOKE_EMITTER_HXX

#include "../vector2d.hpp"

/** */
class SmokeEmitter
{
private:
  FloatVector2d pos;
  float last_particle;
public:
  SmokeEmitter(const FloatVector2d& arg_pos);
  void set_pos(const FloatVector2d& arg_pos);
  void update(float delta);
private:
  SmokeEmitter (const SmokeEmitter&);
  SmokeEmitter& operator= (const SmokeEmitter&);
};

#endif

/* EOF */
