#include <iostream>
#include "../projectile.hxx"
#include "../math.hxx"
#include "../resource_manager.hxx"
#include "../rocket.hxx"
#include "tank.hxx"
#include "turret.hxx"

const float circle = 6.2831854f;

Turret::Turret (Tank* arg_tank, int r_speed, std::string surface, std::string fire) 
  : fire_sur (resources->get_sprite (fire.c_str ())),
    sur (resources->get_sprite (surface.c_str ())),
    shadow (resources->get_sprite ("feuerkraft/turret2_shadow")),
    orientation (0),
    fireing (false),
    reloading (0),
    reloading_speed (r_speed)
{
  tank = arg_tank;
}

Turret::~Turret ()
{
}

void 
Turret::draw (View& view)
{
  float absolute_orientation = tank->get_orientation () + orientation;

#ifdef UGLY_SHADOWS_ENABLED  
  view.draw(shadow, tank->get_pos () + FloatVector2d (10,10), absolute_orientation);
  view.draw(shadow, tank->get_pos () + FloatVector2d (15,15), absolute_orientation);
  view.draw(shadow, tank->get_pos () + FloatVector2d (20,20), absolute_orientation);
  view.draw(shadow, tank->get_pos () + FloatVector2d (25,25), absolute_orientation);
#endif 

  view.draw(sur, tank->get_pos (), absolute_orientation + Math::pi);

  if (fireing && reloading == 0 && tank->ammo > 0.0)
    {
      view.draw(fire_sur, tank->get_pos (), absolute_orientation + Math::pi);
      fireing = false;
      reloading = reloading_speed;
    }
}

void
Turret::update (float delta)
{

  static bool floppy;

  if (reloading)
    reloading--;

  if (fireing && reloading == 0 && tank->ammo > 0.0)
    {
      tank->ammo -=  0.003 * delta;

      float rot_angle = tank->get_orientation() + orientation;
      
      FloatVector2d dir = FloatVector2d::make_polar(10.0 + tank->get_velocity(), rot_angle);

      if (floppy)
	{
	  GameWorld::current()->add (new Projectile (tank, tank->get_pos ()
                                                     + FloatVector2d::make_polar(-5.0f, rot_angle),
                                                     dir));
	}
      else
	{
	  GameWorld::current()->add (new Projectile (tank, tank->get_pos ()
                                                     + FloatVector2d::make_polar(5.0, rot_angle),
                                                     dir));
	}
      floppy = !floppy;
    }
}

void 
Turret::increase_angle (float delta)
{
  orientation += tank->get_increment () * delta;
  //angle = fmod (angle + circle, circle);
}

void
Turret::start_fire ()
{
  fireing = true;
}

void
Turret::stop_fire ()
{
  fireing = false;
}

void 
Turret::set_relative_orientation (float arg_orientation)
{
  orientation = arg_orientation;
}

void
Turret::set_absolute_orientation (float arg_orientation)
{
  orientation = orientation - tank->get_orientation();
}

// EOF 
