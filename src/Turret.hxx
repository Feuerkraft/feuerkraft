#ifndef TURRET_HH
#define TURRET_HH

#include <ClanLib/core.h>
#include <SphriteLib/sphritelibGL.h>
#include "GameObj.hxx"

class Tank;

class Turret : public GameObj
{
private:
  boost::dummy_ptr<Tank> tank;

  //CL_Surface sur;
  //CL_Surface fire_sur;

  SpriteProviderStorage storage;
  Sprite* fire_sur;
  Sprite* sur;

  // The angle of the turent relative to the tank in radians
  float angle;

  bool fireing;
  int  reloading;
  int  reloading_speed;

public:
  Turret (boost::dummy_ptr<GameWorld>  w,
	  Tank*, int reloading_speed, std::string, std::string);
  ~Turret ();

  void draw (View* view);
  void update (float);

  void increase_angle (float delta);
  void decrease_angle (float delta);
  void start_fire ();
  void stop_fire ();
  void set_angle (float angle);
};

#endif // TURRET_HH

// EOF
