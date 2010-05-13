//  $Id: view.hpp,v 1.14 2003/10/20 21:30:09 grumbel Exp $
// 
//  Feuerkraft - A Tank Battle Game
//  Copyright (C) 2000 Ingo Ruhnke <grumbel@gmx.de>
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//  
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//  
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.

#ifndef VIEW_HH
#define VIEW_HH

#include "view_properties.hpp"
#include "vector2d.hpp"
#include "display/drawing_context.hpp"
#include "display/scene_context.hpp"

class CL_Sprite;
class Color;
class DrawingContext;

/** ViewState represents the current configuration of a View, aka.
    rotation, position, zoom, etc. It is passed to the plug-ins to be
    changed. */
struct ViewState
{
  float x_offset;
  float y_offset;
  float zoom;
  float rotation;

  ViewState() :
    x_offset(),
    y_offset(),
    zoom(),
    rotation()
  {}
};

class ViewUpdater
{
public:
  virtual ~ViewUpdater() {}

  virtual void update(float delta, ViewState& state) =0;
};

/** A View provides a 'View' onto the world.
    
A View is similar to a CL_GraphicContext, you can paint on it with
specific operations. It works basically by holding a pointer to
the world and passing a draw() call to the world in the event that
the View needs a draw. A pointer to the View class is passed as
argument to the Worlds draw call. 

FIXME: We need plugable modules for the View so that the zoom,
scale and rotation of the view will be automagically changed
acording to a plugin, possible plugins would be VehicleView,
BuildingView, FixedView, etc. How should clean translation between
plugins be provided? Should that be handled at plugin site?
*/
class View 
{
protected:
  int x1, y1;
  int x2, y2;

  ViewState state;
  ViewUpdater* view_updater;
  ViewProperty properties;
  SceneContext* scene_context;
  
  static View* current_;
public:
  View (int x1, int y1, int x2, int y2, ViewUpdater* arg_updater = 0);
  virtual ~View ();

  static View* current() { return current_; }

  float get_x_offset ();
  float get_y_offset ();

  int get_width ();
  int get_height ();
  
  /** Set the ViewUpdater. \a arg_updater will get deleted once it is
      no longer used */
  void set_updater(ViewUpdater* arg_updater);
  void update(float delta);

  SceneContext& get_sc() { return *scene_context; } 

  bool get_property (ViewProperty p);
  void set_property (ViewProperty p);

  FloatVector2d screen_to_world (const FloatVector2d&);
  FloatVector2d world_to_screen (const FloatVector2d&);

private:
  View(const View&);
  View& operator=(const View&);
};

typedef View* ViewPtr;

#endif

/* EOF */
