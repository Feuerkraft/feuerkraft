#ifndef TANK_HH
#define TANK_HH

#include <ClanLib/core.h>
#include <deque>

#include "GameObj.hh"
#include "Controllable.hh"

class Turret;

class Tank : public Controllable,
	     public GameObj
{
private:
  float angle;
  float speed;
  float velocity;
  float x_pos;
  float y_pos;
  float increment;
  int   inc_step;
  int frame;
  CL_Surface sur;
  CL_Surface smod;
  Turret* turret;

  std::deque<CL_Vector> smodpos;
  float tmp_angle;
  int smod_step;

public:
  Tank (int reloading_speed, std::string tank, std::string turret, std::string fire);
  virtual ~Tank ();
  
  void draw ();
  void update ();

  void increase_angle ();
  void decrease_angle ();
  void set_angle (float);
  Turret* get_turret () { return turret; }

  CL_Vector get_pos () { return CL_Vector(x_pos, y_pos); }
  float get_x_pos () { return x_pos; }
  float get_y_pos () { return y_pos; }
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
};

#endif // TANK_HH

// EOF
