#ifndef TANK_HH
#define TANK_HH

#include <ClanLib/display.h>
#include <SphriteLib/sphritelibGL.h>
#include <deque>

#include "Mine.hxx"
#include "GameObj.hxx"
#include "Controllable.hxx"
#include "Energie.hxx"
#include "Vehicle.hxx"

class Turret;

class Tank : public Controllable,
	     public Vehicle
{
private:
  float angle; //FIXME: Degree or Radian?
  float speed;
  float velocity;
  float increment;
  int   inc_step;
  int frame;

  /*CL_Surface sur;*/
  CL_Surface smod;
  CL_Surface sur_destroyed;

  Sprite sur;
  Sprite shadow;

  Turret* turret;

  std::deque<CL_Vector> smodpos;
  float tmp_angle;
  int smod_step;
  int mine_reload_time;
  Energie energie;
  bool destroyed;
  float particle_release;

public:
  friend class Turret;

  Tank (boost::dummy_ptr<GameWorld>  w, const CL_Vector &arg_pos,
	int reloading_speed, std::string tank, std::string turret, std::string fire);
  virtual ~Tank ();
  
  void draw (View* view);
  void update (float);

  void explode ();

  void increase_angle (float delta);
  void decrease_angle (float delta);
  void set_angle (float);
  Turret* get_turret () { return turret; }

  float get_angle () { return angle; }
  float get_increment () { return increment; }

  // Implementing Controllable
  float get_acceleration () { return increment; }
  float get_max_forward_velocity () { return 1.0; }
  float get_max_backward_velocity () { return -1.0; }
  float get_turn_speed () { return 1.0; }

  void turn_left (float delta) { increase_angle (delta); }
  void turn_right (float delta) { decrease_angle (delta); }

  void turn_left2 (float delta);
  void turn_right2 (float delta);

  void increase_velocity (float delta);
  void decrease_velocity (float delta);
  
  void start_fire ();
  void stop_fire ();

  void drop_mine ();
  
  int get_z_pos () { return destroyed ? 0 : 50; }

  bool is_colliding (CL_Vector obj_pos);

  void collide (Projectile*);
  void collide (Mine*);
  virtual void collide (CL_Vector force);

  virtual float get_physical_size () { return 3.0; }
  float get_velocity ();
};

#endif // TANK_HH

// EOF
