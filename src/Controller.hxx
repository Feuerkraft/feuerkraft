#ifndef CONTROLLER_HH
#define CONTROLLER_HH

#include "Controllable.hxx"

class Controllable;

class Controller
{
protected:  
  Controllable* controllable;

public:
  Controller (Controllable* obj);
  virtual ~Controller () {
  }

  virtual void update (float delta) =0;
  virtual void set_controllable (Controllable* obj) { controllable = obj; }
};

#endif // CONTROLLER_HH
