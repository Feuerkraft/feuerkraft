//  $Id: smoke_particle.hpp,v 1.9 2003/06/07 16:16:08 grumbel Exp $
// 
//  Feuerkraft - A Tank Battle Game
//  Copyright (C) 2000 Ingo Ruhnke <grumbel@gmx.de>
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

#ifndef SMOKEPARTICLE_HXX
#define SMOKEPARTICLE_HXX

#include "../view.hpp"
#include "../resource_manager.hpp"
#include "particle.hpp"

class SmokeParticle : public Particle
{
private:
  CL_Sprite sprite;
  float size;
  float angle;
  float max_life_time;
public:
  SmokeParticle(const FloatVector2d& arg_pos)
  {
    pos = arg_pos;
    size = 1;
    angle = rand () % 360;    
    sprite = resources->get_sprite("feuerkraft/smoke");
    max_life_time = 10.0f;
    life_time = max_life_time;
    //velocity = FloatVector2d (80.0f, 0.0f);
  }

  virtual ~SmokeParticle ()
  {
  }

  void update (float delta) 
  {
    pos += GameWorld::current()->get_wind() * delta;

    Particle::update (delta);

    life_time -= delta;
  }

  void draw (View& view) 
  {    
    sprite.set_alpha ((life_time/max_life_time) * .3);
    sprite.set_scale (0.8f + ((1 - life_time/max_life_time)) * 4.0f,
		       0.8f + ((1 - life_time/max_life_time)) * 4.0f);
    sprite.set_angle(angle);
    view.get_sc().color().draw(sprite, pos.x, pos.y);
  }

  float get_z_pos () { return 100; }
};

#endif

/* EOF */
