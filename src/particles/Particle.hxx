//  $Id: Particle.hxx,v 1.1 2002/03/10 17:00:34 grumbel Exp $
// 
//  Pingus - A free Lemmings clone
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
#include "../GameObj.hxx"

class Particle : public GameObj
{
public: // FIXME: Probally a bad idea?!
  CL_Vector pos;
  CL_Vector velocity;
  CL_Vector acceleration;

  // Lifetime of the particle in seconds
  float life_time;

public:
  Particle (boost::dummy_ptr<GameWorld> world)
    : GameObj (world)
  {}

  virtual ~Particle () {}

  virtual void update (float delta) {
    life_time -= delta;
    
    pos += velocity * delta;
    velocity += acceleration * delta;
  }

  virtual bool alive () { return life_time > 0; }
  CL_Vector get_pos () { return pos; }

  bool removable () { return !alive (); }
};

#endif

/* EOF */
