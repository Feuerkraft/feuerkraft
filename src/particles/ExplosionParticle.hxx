//  $Id: ExplosionParticle.hxx,v 1.7 2002/04/02 09:52:57 grumbel Exp $
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

#ifndef EXPLOSIONPARTICLE_HXX
#define EXPLOSIONPARTICLE_HXX

#include <ClanLib/display2.h>
#include "Particle.hxx"
#include "../ResourceManager.hxx"

class ExplosionParticle : public Particle
{
private:
  float size;
  CL_Sprite* sprite;
  float max_life_time;
  bool direction;
  float angle;
public:
  ExplosionParticle (boost::dummy_ptr<GameWorld> world,
		     const CL_Vector& arg_pos, const CL_Vector& arg_vel, float arg_size)
    : Particle (world)
  {
    velocity = arg_vel;
    pos = arg_pos;

    life_time = ((rand() % 10) / 40.0f) + .5;
    max_life_time = life_time;

    size = arg_size;

    direction = rand () % 2;

    angle = rand () % 360;

    // FIXME: memory leak
    sprite = resources->get_sprite_ptr ("feuerkraft/explosion");
    sprite->rotate (angle);
    //std::cout << "Angle: " << angle << std::endl;
  }

  void update (float delta) {
    Particle::update (delta);
    
    if (direction)
      {
	angle += .5f * delta;
      }
    else
      {
	angle -= .5f * delta;
      }
  }
  
  void draw (View* view) 
  {
    if (life_time > 0)
      {
	//std::cout << "Drawing particle:" << life_time << " pos: " << pos << " angle:" << angle << std::endl;

	//std::cout << "Angle: " << sprite->getAngle () << std::endl;

	float alpha = 1.0f - (life_time/max_life_time);

	sprite->set_alpha (1.0f - (alpha * alpha));

	sprite->set_scale (((1 - life_time/max_life_time)) * size,
			   ((1 - life_time/max_life_time)) * size);
	view->draw(sprite, pos, angle);
      }
  }

  int get_z_pos () { return 200; }
};

#endif

/* EOF */
