#ifndef CONTROLLER_HH
#define CONTROLLER_HH

#include "Controllable.hh"

class Controller
{
protected:  
  Controllable* controllable;

public:
  Controller (Controllable* obj) :
    controllable (obj)
  {}

  virtual ~Controller () {
  }

  virtual void update () =0;
};

#endif // CONTROLLER_HH
