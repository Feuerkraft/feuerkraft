//  $Id: view.hxx,v 1.11 2003/06/03 14:11:22 grumbel Exp $
// 
//  Feuerkraft - A Tank Battle Game
//  Copyright (C) 2000 Ingo Ruhnke <grumbel@gmx.de>
//
//  This program is free software; you can redistribute it and/or
//  modify it under the terms of the GNU General Public License
//  as published by the Free Software Foundation; either version 2
//  of the License, or (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
// 
//  You should have received a copy of the GNU General Public License
//  along with this program; if not, write to the Free Software
//  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

#ifndef VIEW_HH
#define VIEW_HH

#include "view_properties.hxx"
#include "vector2d.hxx"

class CL_Sprite;
class CL_Surface;
class Color;

/** ViewState represents the current configuration of a View, aka.
    rotation, position, zoom, etc. It is passed to the plug-ins to be
    changed. */
struct ViewState
{
  float x_offset;
  float y_offset;
  float zoom;
  float rotation;
};

class ViewUpdater
{
public:
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
public:
  View (int x1, int y1, int x2, int y2, ViewUpdater* arg_updater = 0);
  virtual ~View ();

  void set_view (int x_pos, int y_pos);

  /** Set the zoom of the current view, a zoom of 1.0 is normal, >1.0
      is enlarged */
  void set_zoom (float zoom);

  float get_x_offset ();
  float get_y_offset ();

  int get_width ();
  int get_height ();
  int get_x1 ();
  int get_x2 ();
  int get_y1 ();
  int get_y2 ();
  
  /** Set the ViewUpdater. \a arg_updater will get deleted once it is
      no longer used */
  void set_updater(ViewUpdater* arg_updater);
  void update(float delta);

  void draw (CL_Sprite& sprite, const FloatVector2d& pos, float angle = 0.0);
  void draw (CL_Surface& sur, const FloatVector2d& pos);
  void draw (CL_Surface& sur, float x_pos, float y_pos);
  void draw (CL_Surface& sur, float x_pos, float y_pos, int frame);
  void draw (CL_Surface& sur, float x_pos, float y_pos, 
	     float size_x, float size_y, int frame);


  void draw_line (float x1, float y1, float x2, float y2, 
		  const Color& color);
  void draw_fillrect (float x1, float y1, float x2, float y2, 
		      const Color& color);
  void draw_rect (float x1, float y1, float x2, float y2, 
		  const Color& color);
  void draw_pixel (float x_pos, float y_pos, 
		   const Color& color);
  void draw_circle (float x_pos, float y_pos, float radius,
                    const Color& color);

  /** Draws an arc, starting from angle_start to angle_end in
      counterclockwise direction. Angles are taken in radian */
  void draw_arc (float x_pos, float y_pos, float radius, float angle_start, float angle_end,
                 const Color& color);

  bool get_property (ViewProperty p);
  void set_property (ViewProperty p);

  FloatVector2d screen_to_world (const FloatVector2d&);
  FloatVector2d world_to_screen (const FloatVector2d&);
};

typedef View* ViewPtr;

#endif

/* EOF */
