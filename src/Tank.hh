#ifndef TANK_HH
#define TANK_HH

#include <ClanLib/core.h>
#include <deque>

#include "Mine.hh"
#include "GameObj.hh"
#include "Controllable.hh"
#include "Collideable.hh"
#include "Energie.hh"

class Turret;

class Tank : public Controllable,
	     public GameObj,
	     public Collideable
{
private:
  float angle;
  float speed;
  float velocity;
  CL_Vector pos;
  float increment;
  int   inc_step;
  int frame;
  CL_Surface sur;
  CL_Surface smod;
  CL_Surface sur_destroyed;
  Turret* turret;

  std::deque<CL_Vector> smodpos;
  float tmp_angle;
  int smod_step;
  int mine_reload_time;
  Energie energie;
  bool destroyed;

public:
  Tank (int reloading_speed, std::string tank, std::string turret, std::string fire);
  virtual ~Tank ();
  
  void draw ();
  void update (float);

  void increase_angle (float delta);
  void decrease_angle (float delta);
  void set_angle (float);
  Turret* get_turret () { return turret; }

  CL_Vector get_pos () { return pos; }

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
};

#endif // TANK_HH

// EOF
