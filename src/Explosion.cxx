//  $Id: Explosion.cxx,v 1.3 2002/03/10 19:51:42 grumbel Exp $
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

#include "Shockwave.hxx"
#include "Explosion.hxx"
#include "particles/ExplosionParticle.hxx"

Explosion::Explosion (boost::dummy_ptr<GameWorld>  w,
		      const CL_Vector& arg_pos, Size arg_size) 
  : GameObj (w),
    is_drawn (false),
    pos (arg_pos),
    size (arg_size)
{

  new_particle_time = 0.0f;

  switch (size)
    {
    case SMALL:
    case LARGE:
      explo = CL_Surface("feuerkraft/smallexplo", resources);
      lifetime = 1;
      
      break;
    case MEDIUM:
      explo = CL_Surface("feuerkraft/mediumexplo", resources);
      lifetime = 25;
      world->add (new Shockwave (world, pos));
      break;
    }

  lifetime = .5f;

  new_particle_time = 1.0f;
};

void 
Explosion::draw (View* view) 
{
  /*view->draw (explo,
	      int(pos.x) - explo.get_width ()/2,
	      int(pos.y) - explo.get_height ()/2);
	      is_drawn = true;*/
}
  
void 
Explosion::update (float delta) 
{
  lifetime -= delta;

  new_particle_time += delta;
  
  if (new_particle_time > 0.7)
    {
      for (int i = 0; i < 6; ++i)
	{
	  world->add_front (new ExplosionParticle (get_world (),
						   CL_Vector (pos.x + (rand()%10 - 5), 
							      pos.y + (rand()%10 - 5)),
						   CL_Vector (rand ()%20 - 10, rand ()%20 - 10), 
						   (rand() % 10) / 30.f));
	}
      
      new_particle_time = 0;
    }
}

bool 
Explosion::removable () 
{
  //std::cout << "Lifetime: " << lifetime << std::endl;

  return lifetime <= 0;
}

int 
Explosion::get_z_pos () 
{
  return 115; 
}


/* EOF */
