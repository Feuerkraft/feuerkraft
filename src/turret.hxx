#ifndef TURRET_HH
#define TURRET_HH

#include "game_obj.hxx"

class Tank;

class Turret : public GameObj
{
private:
  Tank* tank;

  CL_Sprite fire_sur;
  CL_Sprite sur;
  CL_Sprite shadow;

  // The angle of the turent relative to the tank in radians
  float orientation;

  bool fireing;
  int  reloading;
  int  reloading_speed;

public:
  Turret (Tank*, int reloading_speed, std::string, std::string);
  ~Turret ();

  void draw (View* view);
  void update (float);

  void increase_angle (float delta);
  void decrease_angle (float delta);
  void start_fire ();
  void stop_fire ();
  
  void set_absolute_orientation (float orientation);
  void set_relative_orientation (float orientation);
};

#endif // TURRET_HH

// EOF
