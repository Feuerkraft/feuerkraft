#ifndef CONTROLLABLE_HH
#define CONTROLLABLE_HH

class Controllable 
{
private:
public:
  Controllable () {}
  virtual ~Controllable () {}
  virtual float get_acceleration () { return 0.0; }
  virtual float get_max_forward_velocity () { return 0.0; }
  virtual float get_max_backward_velocity () { return 0.0; }
  virtual float get_turn_speed ()   =0;

  virtual void turn_left ()  =0;
  virtual void turn_right () =0;

  virtual void increase_velocity () {};
  virtual void decrease_velocity () {};
  virtual void start_fire () =0;
  virtual void stop_fire () =0;
};

#endif 
