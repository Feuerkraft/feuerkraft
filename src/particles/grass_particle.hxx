//  $Id: grass_particle.hxx,v 1.2 2003/04/19 23:17:53 grumbel Exp $
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

#ifndef GRASSPARTICLE_HXX
#define GRASSPARTICLE_HXX

#include "particle.hxx"
#include "../resource_manager.hxx"

class GrassParticle : public Particle
{
private:
  CL_Sprite* sprite;
  float size;
  float angle;
  float max_life_time;
  
public:
  GrassParticle (boost::dummy_ptr<GameWorld> world, const CL_Vector& arg_pos)
    : Particle (world)
  {
    pos = arg_pos;
    size = 1;
    angle = rand () % 360;    
    sprite = resources->get_sprite_ptr ("feuerkraft/grasssmoke");
    max_life_time = 10.0f;
    life_time = max_life_time;
    //velocity = CL_Vector (80.0f, 0.0f);
  }

  virtual ~GrassParticle ()
  {
    delete sprite;
  }

  void update (float delta) {
    Particle::update (delta);

    life_time -= delta;
  }

  void draw (View* view) 
  {    
    sprite->set_alpha ((life_time/max_life_time) * 0.4);
    sprite->set_scale (0.8f + ((1 - life_time/max_life_time)) * 4.0f,
		       0.8f + ((1 - life_time/max_life_time)) * 4.0f);
    view->draw(sprite, pos, angle);
  }

  int get_z_pos () { return 100; }
};

#endif

/* EOF */