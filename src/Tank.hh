#ifndef TANK_HH
#define TANK_HH

#include <ClanLib/core.h>
#include <deque>

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
  Turret* turret;

  std::deque<CL_Vector> smodpos;
  float tmp_angle;
  int smod_step;
  int mine_reload_time;
  Energie energie;

public:
  Tank (int reloading_speed, std::string tank, std::string turret, std::string fire);
  virtual ~Tank ();
  
  void draw ();
  void update ();

  void increase_angle ();
  void decrease_angle ();
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

  void turn_left () { increase_angle (); }
  void turn_right () { decrease_angle (); }

  void increase_velocity ();
  void decrease_velocity ();
  
  void start_fire ();
  void stop_fire ();

  void drop_mine ();
  
  int get_z_pos () { return 50; }

  bool is_colliding (CL_Vector obj_pos);

  void collide (Projectile*);
};

#endif // TANK_HH

// EOF
