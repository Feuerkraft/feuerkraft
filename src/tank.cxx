#include <ClanLib/Display/display.h>
#include <iostream>
#include <string>

#include "mine.hxx"
#include "turret.hxx"
#include "tank.hxx"
#include "groundmap/ground_map.hxx"
#include "buildings/building_map.hxx"
#include "particles/smoke_particle.hxx"
#include "particles/grass_particle.hxx"
#include "resource_manager.hxx"
#include "collision_manager.hxx"

const float circle = 6.2831854f;

// FIXME: Global variable hack, remove as soon as possible
#include "vehicle_view.hxx"
extern VehicleView* vehicle_view;

Tank::Tank (const CL_Vector &arg_pos,
	    int reloading_speed, std::string tank, std::string str_turret, std::string fire) 
  : orientation (3.14159f/2.0f),
    speed (0.0f),
    velocity (0.0f),
    increment (0.06f),
    smod (resources->get_sprite (tank.c_str ())),
    sur_destroyed (resources->get_sprite ("feuerkraft/tank2destroyed")),
    sur (resources->get_sprite (tank.c_str ())),
    shadow (resources->get_sprite ("feuerkraft/tank2_shadow")),
    turret (NULL),
    smod_step (0),
    mine_reload_time (0),
    energie (100),
    destroyed (false)
{
  sur.set_alignment(origin_center);
  sur_destroyed.set_alignment(origin_center);

  turret = new Turret(this, reloading_speed, str_turret, fire);
  pos = arg_pos;

  particle_release = 0.0f;
}

Tank::~Tank ()
{
  delete turret;
}

void
Tank::draw_energie (View* view)
{
  energie.draw (view, 
		int(pos.x), int(pos.y - 40));
}
  
void
Tank::draw_levelmap (LevelMap* levelmap)
{
  CL_Display::fill_rect (CL_Rect(int(pos.x / 40), int(pos.y / 40),
				 int(pos.x / 40) + 4, int(pos.y / 40) + 4),
			 CL_Color(255, 0, 0, 255));
}

void
Tank::draw (View* view)
{
  if (destroyed)
    {
      view->draw (sur_destroyed, pos);
    }
  else
    {
      for (std::deque<CL_Vector>::iterator i = smodpos.begin ();
	   i != smodpos.end (); ++i)
	{
	  /*view->draw (smod, 
		      int(i->x - (smod.get_width ()/2)),
		      int(i->y - (smod.get_height ()/2)),
		      int(fmod (i->z, circle) / circle * 16.0));*/
	  //view->draw (smod, 
	}

#ifdef UGLY_SHADOWS_ENABLED
      view->draw(shadow, pos + CL_Vector (0,0), orientation);
      view->draw(shadow, pos + CL_Vector (5,5), orientation);
      view->draw(shadow, pos + CL_Vector (10,10), orientation);
      view->draw(shadow, pos + CL_Vector (15,15), orientation);
#endif /* UGLY_SHADOWS_ENABLED */

      // Draw the tank
      view->draw(sur, pos, orientation);
      turret->draw (view);

      // Draw Collision rect
      CL_Vector x1 (-30, -15);
      CL_Vector y1 (-30, 15);
      CL_Vector x2 (30, -15);
      CL_Vector y2 (30, 15);

      x1 = x1.rotate (orientation,
		 CL_Vector (0.0, 0.0, 1.0));
      y1 = y1.rotate (orientation,
		 CL_Vector (0.0, 0.0, 1.0));
      x2 = x2.rotate (orientation,
		 CL_Vector (0.0, 0.0, 1.0));
      y2 = y2.rotate (orientation,
		 CL_Vector (0.0, 0.0, 1.0));      

      x1 += pos;
      y1 += pos;
      x2 += pos;
      y2 += pos;

      /*view->draw_line (x1.x, x1.y, x2.x, x2.y, 1.0, 1.0, 1.0);
      view->draw_line (y1.x, y1.y, y2.x, y2.y, 1.0, 1.0, 1.0);
      view->draw_line (y2.x, y2.y, x2.x, x2.y, 1.0, 1.0, 1.0);
      view->draw_line (y1.x, y1.y, x1.x, x1.y, 1.0, 1.0, 1.0);*/
    }
}

void 
Tank::explode ()
{
  GameWorld::current()->add (new Explosion (pos, Explosion::MEDIUM));
  destroyed = true;
  destroy_time = CL_System::get_time ();
}

void
Tank::respawn ()
{
  /* FIXME: This respawn code is extremly ugly... */
  Tank* tank = new Tank(CL_Vector (560, 1245), 5, "feuerkraft/tank2", "feuerkraft/turret2", "feuerkraft/fire2");
  GameWorld::current()->add (tank);
  if (get_controller ())
    {
      get_controller ()->set_controllable (tank);
      tank->set_controller (get_controller ());
      vehicle_view->set_vehicle (tank);
    }
  destroy_time = -1;
}

void 
Tank::update (float delta)
{
  // FIXME: Ugly
  if (destroyed && destroy_time != -1 && destroy_time + 2000 < (int) CL_System::get_time ())
    {
      respawn ();
    }

  particle_release += fabs(velocity);

  if (particle_release > 20.0f && !destroyed)
    {
      GroundType type = GameWorld::current()->get_groundmap ()->get_groundtype (pos.x, pos.y);

      if (type == GT_SAND)
	GameWorld::current()->add (new SmokeParticle(pos));
      else if (type == GT_GRASS)
	GameWorld::current()->add (new GrassParticle(pos));

      particle_release = 0;
    }
  
  delta = delta * 50.0f;

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
  if (velocity > 5)
    velocity = 5.0f;
  else if (velocity < -2)
    velocity = -2.0f;

  CL_Vector vel (-velocity, 0.0);
  vel = vel.rotate (orientation, // - fmod(orientation, circle/16.0), 
		    CL_Vector (0.0, 0.0, 1.0));

  if (velocity != 0.0 || tmp_angle != orientation)
    {
      if (smod_step++ > 5)
	{
	  smod_step = 0;
	  tmp_angle = orientation;
	  smodpos.push_back (CL_Vector (pos.x, pos.y, orientation));
	  if (smodpos.size () > 200)
	    smodpos.pop_front ();
	}
    }

  CL_Vector tmp_pos = pos + (vel * delta);

  if (!(GameWorld::current()->get_buildingmap ()->get_building (CL_Vector(pos.x, tmp_pos.y))))
    {
      //pos = tmp_pos; // We collided with a building
      //velocity = 0;
      pos.y = tmp_pos.y;
    }
  else
    {
      velocity /= delta;
    }

  if (!(GameWorld::current()->get_buildingmap ()->get_building (CL_Vector(tmp_pos.x, pos.y))))
    {
      //pos = tmp_pos; // We collided with a building
      //velocity = 0;
      pos.x = tmp_pos.x;
    }
  else
    {
      velocity /= delta;
    }

  CollisionManager::current()->add_rect(get_id(), pos.x, pos.y, 30, 68, orientation);
}

void 
Tank::increase_angle (float delta)
{
  if (velocity >= 0)
    orientation += increment * delta;
  else
    orientation += increment * delta;
  //orientation = fmod (orientation + circle, circle);
}

void
Tank::decrease_angle (float delta)
{
  if (velocity >= 0)
    orientation -= increment * delta;
  else
    orientation -= increment * delta;
  //orientation = fmod (orientation + circle, circle);
}

void
Tank::set_angle (float arg_orientation)
{
  orientation = arg_orientation;
}

void 
Tank::increase_velocity (float delta)
{
  velocity += 0.3f * delta;

  fuel -= 0.0001 * delta;
}

void
Tank::decrease_velocity (float delta)
{
  velocity -= 0.3f * delta;
}

void 
Tank::turn_left2 (float delta) 
{
  turret->increase_angle (delta); 
}

void
Tank::turn_right2 (float delta) 
{ 
  turret->decrease_angle (delta); 
}

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
      CL_Vector vel = CL_Vector (25.0, 0.0, 0.0).rotate (orientation,
							 CL_Vector (0.0, 0.0, 1.0));

      GameWorld::current()->add(new Mine(CL_Vector(pos.x, pos.y) + vel));
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

void
Tank::on_collision_with_building(Building* building)
{
  std::cout << "Tank: collision with building " << get_id() << std::endl;
}

void
Tank::on_collision(GameObj* obj)
{
  std::cout << "Tank: collision from " << get_id() << " with: " << obj->get_id() << std::endl;
}

// EOF //

