//  $Id: particle.hxx,v 1.6 2003/06/03 14:11:22 grumbel Exp $
// 
//  Feuerkraft - A Tank Battle Game
//  Copyright (C) 2000 Ingo Ruhnke <grumbel@gmx.de>
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

#ifndef PARTICLE_HXX
#define PARTICLE_HXX

#include <ClanLib/core.h>
#include "../game_obj.hxx"

class Particle : public GameObj
{
public:
  FloatVector2d pos;
  FloatVector2d velocity;
  FloatVector2d acceleration;

  // Lifetime of the particle in seconds
  float life_time;

public:
  Particle () {}
  virtual ~Particle () {}

  virtual void update (float delta) {
    life_time -= delta;
    
    pos += velocity * delta;
    velocity += acceleration * delta;
  }

  virtual bool alive () { return life_time > 0; }
  FloatVector2d get_pos () { return pos; }

  bool removable () { return !alive (); }
};

#endif

/* EOF */
