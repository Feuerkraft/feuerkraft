#ifndef CONTROLLER_HH
#define CONTROLLER_HH

#include "controllable.hxx"

class Controllable;

/** FIXME: This interface class needs to be completely rewritten,
    since passing the controller data directly to the client could
    make it difficult to track and record them. Letting the
    Controllable poll the data from the controller would/could be a
    better idea. */
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
  virtual Controllable* get_controllable () { return controllable; }

  /* Pseudo Code:

     float get_horizontal_axis ();
     float get_vertical_axis ();
     float get_strafe_axis ();

     bool get_primary_button ();
     bool get_secondary_button ();
     
     bool get_use_button ();
     bool get_comm_button ();
   */
};

#endif // CONTROLLER_HH
