#include <iostream>
#include <string>
#include <ClanLib/core.h>
#include <ClanLib/gl.h>

#include "Mine.hh"
#include "Turret.hh"
#include "Tank.hh"

const float circle = 6.2831854f;
extern CL_ResourceManager* resources;

Tank::Tank (boost::dummy_ptr<GameWorld>  w, const CL_Vector &arg_pos,
	    int reloading_speed, std::string tank, std::string str_turret, std::string fire) 
  : Vehicle (w),
    angle (0.0f),
    speed (0.0f),
    velocity (0.0f),
    increment (0.06f),
    inc_step (0),
    smod ("feuerkraft/smod", resources),
    sur_destroyed ("feuerkraft/tankdestroyed", resources),
    turret (NULL),
    smod_step (0),
    mine_reload_time (0),
    energie (100),
    destroyed (false)
{
  turret = new Turret(world, this, reloading_speed, str_turret, fire);
  pos = arg_pos;

  storage.add (new SpriteProvider (tank.c_str (), resources));
  sur = storage.create (tank.c_str ());
}

Tank::~Tank ()
{
  delete turret;
}
  
void
Tank::draw (View* view)
{
  if (destroyed)
    {
      view->draw (sur_destroyed, 
		  pos.x - sur_destroyed.get_width ()/2,
		  pos.y - sur_destroyed.get_height ()/2);
    }
  else
    {
      int frame = int(fmod (angle, circle) / circle * 16.0);
  
      for (std::deque<CL_Vector>::iterator i = smodpos.begin ();
	   i != smodpos.end (); ++i)
	{
	  /*view->draw (smod, 
		      int(i->x - (smod.get_width ()/2)),
		      int(i->y - (smod.get_height ()/2)),
		      int(fmod (i->z, circle) / circle * 16.0));*/
	  //view->draw (smod, 
	}

      /*view->draw (sur, int(pos.x) - (sur.get_width ()/2),
		  int(pos.y) - (sur.get_height ()/2),
		  frame);*/

      /*view->draw (sur, int(pos.x) - (sur.get_width ()/2),
	int(pos.y) - (sur.get_height ()/2));*/

      /*glBegin (GL_LINES);
      glVertex2f (view->get_x_offset () + pos.x,
		  view->get_x_offset () + pos.y);
      glVertex2f (view->get_x_offset () + pos.x + 100,
		  view->get_x_offset () + pos.y);
		  glEnd ();*/

      sur->draw(view->get_x_offset () + pos.x,
		view->get_y_offset () + pos.y,
		angle/(circle/2.0)*180);

      turret->draw (view);

      // Draw Collision rect
      CL_Vector x1 (-30, -15);
      CL_Vector y1 (-30, 15);
      CL_Vector x2 (30, -15);
      CL_Vector y2 (30, 15);

      //std::cout << "Angle: " << angle << std::endl;
      x1 = x1.rotate (angle - fmod(angle, circle/16.0),
		 CL_Vector (0.0, 0.0, 1.0));
      y1 = y1.rotate (angle - fmod(angle, circle/16.0),
		 CL_Vector (0.0, 0.0, 1.0));
      x2 = x2.rotate (angle - fmod(angle, circle/16.0),
		 CL_Vector (0.0, 0.0, 1.0));
      y2 = y2.rotate (angle - fmod(angle, circle/16.0),
		 CL_Vector (0.0, 0.0, 1.0));      

      x1 += pos;
      y1 += pos;
      x2 += pos;
      y2 += pos;

      /*view->draw_line (x1.x, x1.y, x2.x, x2.y, 1.0, 1.0, 1.0);
      view->draw_line (y1.x, y1.y, y2.x, y2.y, 1.0, 1.0, 1.0);
      view->draw_line (y2.x, y2.y, x2.x, x2.y, 1.0, 1.0, 1.0);
      view->draw_line (y1.x, y1.y, x1.x, x1.y, 1.0, 1.0, 1.0);*/

      energie.draw (view, 
		    pos.x, pos.y - 40);
    }
}

void 
Tank::explode ()
{
  world->add (new Explosion (world, pos, Explosion::MEDIUM));
  destroyed = true;
  Tank* tank = new Tank (world, CL_Vector (400, 0), 5, "feuerkraft/tank2", "feuerkraft/turret2", "feuerkraft/fire2");
  world->add (tank);
  if (get_controller ())
    {
      get_controller ()->set_controllable (tank);
      tank->set_controller (get_controller ());
    }
}

void 
Tank::update (float delta)
{
  if (destroyed)
    return;

  if (energie <= 0)
    explode ();
  
  turret->update (delta);

  if (mine_reload_time)
    --mine_reload_time;

  if (velocity > 0.06f)
    velocity -= 0.05f;
  else if (velocity < -0.06f)
    velocity += 0.05f;
  else
    velocity = 0;

  // Terminal velocity
  if (velocity > 2)
    velocity = 2.0f;
  else if (velocity < -1)
    velocity = -1.0f;

  CL_Vector vel (-velocity, 0.0);
  vel = vel.rotate (angle, // - fmod(angle, circle/16.0), 
		    CL_Vector (0.0, 0.0, 1.0));

  if (velocity != 0.0 || tmp_angle != angle)
    {
      if (smod_step++ > 5)
	{
	  smod_step = 0;
	  tmp_angle = angle;
	  smodpos.push_back (CL_Vector (pos.x, pos.y, angle));
	  if (smodpos.size () > 200)
	    smodpos.pop_front ();
	}
    }

  pos = pos + (vel * delta);
}

void 
Tank::increase_angle (float delta)
{
  if (velocity >= 0)
    angle += increment * delta;
  else
    angle += increment * delta;
  //angle = fmod (angle + circle, circle);
}

void
Tank::decrease_angle (float delta)
{
  if (velocity >= 0)
    angle -= increment * delta;
  else
    angle -= increment * delta;
  //angle = fmod (angle + circle, circle);
}

void
Tank::set_angle (float arg_angle)
{
  angle = angle;
}

void 
Tank::increase_velocity (float delta)
{
  velocity += 0.5f * delta;

  fuel -= 0.0001 * delta;
}

void
Tank::decrease_velocity (float delta)
{
  velocity -= 0.5f * delta;
}

void 
Tank::turn_left2 (float delta) { turret->increase_angle (delta); }
void
Tank::turn_right2 (float delta) { turret->decrease_angle (delta); }

void 
Tank::start_fire ()
{
  turret->start_fire ();
}

void 
Tank::stop_fire ()
{
  turret->stop_fire ();
}

void
Tank::drop_mine ()
{
  if (mine_reload_time <= 0)
    {
      CL_Vector vel = CL_Vector (25.0, 0.0, 0.0).rotate (angle - fmod(angle, circle/16.0), CL_Vector (0.0, 0.0, 1.0));

      world->add (new Mine (world, CL_Vector(pos.x, pos.y) + vel));
      mine_reload_time = 50;
    }
}

bool 
Tank::is_colliding (CL_Vector obj_pos)
{
  float range = 10.0; 

  return  (obj_pos.x > pos.x - range && obj_pos.x < pos.x + range
	   && obj_pos.y > pos.y - range && obj_pos.y < pos.y + range);
}

void 
Tank::collide (Projectile*)
{
  energie -= 5;
}

void 
Tank::collide (Mine*)
{
  energie -= 25;
}

void 
Tank::collide (CL_Vector force)
{
  energie -= int(force.norm ());
  
  std::cout << "Tank: Got force: " << force.norm () << std::endl;
}

float 
Tank::get_velocity ()
{
  return velocity;
}

// EOF //

