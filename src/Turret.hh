#ifndef TURRET_HH
#define TURRET_HH

#include <ClanLib/core.h>

#include "GameObj.hh"

class Tank;

class Turret : public GameObj
{
private:
  Tank* tank;

  CL_Surface sur;
  CL_Surface fire_sur;

  // The angle of the turent relative to the tank in radians
  float angle;

  bool fireing;
  int  reloading;
  int  reloading_speed;

public:
  Turret (Tank*, int reloading_speed, std::string, std::string);
  ~Turret ();

  void draw ();
  void update (float);

  void increase_angle ();
  void decrease_angle ();
  void start_fire ();
  void stop_fire ();
  void set_angle (float angle);
};

#endif // TURRET_HH

// EOF
