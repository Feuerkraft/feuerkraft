//  $Id: SmokeParticle.hxx,v 1.4 2002/04/02 09:52:57 grumbel Exp $
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

#ifndef SMOKEPARTICLE_HXX
#define SMOKEPARTICLE_HXX

#include "Particle.hxx"
#include "ResourceManager.hxx"

class SmokeParticle : public Particle
{
private:
  CL_Sprite* sprite;
  float size;
  float angle;
  float max_life_time;
public:
  SmokeParticle (boost::dummy_ptr<GameWorld> world, const CL_Vector& arg_pos)
    : Particle (world)
  {
    pos = arg_pos;
    size = 1;
    angle = rand () % 360;    
    sprite = resources->get_sprite_ptr ("feuerkraft/sandsmoke");
    max_life_time = 10.0f;
    life_time = max_life_time;
    //velocity = CL_Vector (80.0f, 0.0f);
  }

  virtual ~SmokeParticle ()
  {
    delete sprite;
  }

  void update (float delta) {
    Particle::update (delta);

    life_time -= delta;
  }

  void draw (View* view) 
  {    
    sprite->set_alpha ((life_time/max_life_time) * 0.3);
    sprite->set_scale (0.8f + ((1 - life_time/max_life_time)) * 4.0f,
		       0.8f + ((1 - life_time/max_life_time)) * 4.0f);
    view->draw(sprite, pos, angle);
  }

  int get_z_pos () { return 100; }
};

#endif

/* EOF */
