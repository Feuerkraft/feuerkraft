//  $Id: view.hxx,v 1.2 2003/04/19 23:17:52 grumbel Exp $
// 
//  Pingus - A free Lemmings clone
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

#include <ClanLib/core.h>
#include <ClanLib/display.h>
#include "boost/dummy_ptr.hpp"
#include "gui_obj.hxx"
#include "game_world.hxx"
#include "view_properties.hxx"

class GameWorld;

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
  : public GuiObj
{
protected:
  CL_GraphicContext* gc;
  boost::dummy_ptr<GameWorld> world;
  int x1, y1;
  int x2, y2;
  int x_offset, y_offset;
  float zoom;
  float rotation;
  ViewProperty properties;
public:
  View (boost::dummy_ptr<GameWorld> world,
	int x1, int y1, int x2, int y2,
	int x_offset = 0, int y_offset = 0,
	CL_GraphicContext* arg_gc = 0);
  virtual ~View ();

  CL_GraphicContext* get_gc ();
  void set_gc (CL_GraphicContext* arg_gc);
  
  void draw (CL_GraphicContext* gc);
  void set_view (int x_pos, int y_pos);

  /** Set the zoom of the current view, a zoom of 1.0 is normal, >1.0
      is enlarged */
  void set_zoom (float zoom);

  virtual void update (float delta);
  int get_x_offset ();
  int get_y_offset ();
  int get_width ();
  int get_height ();
  int get_x1 ();
  int get_x2 ();
  int get_y1 ();
  int get_y2 ();

  void draw (CL_Sprite* sprite, const CL_Vector& pos, float angle = 0.0);
  void draw (CL_Sprite& sprite, const CL_Vector& pos, float angle = 0.0);
  void draw (CL_Surface& sur, const CL_Vector& pos);
  void draw (CL_Surface& sur, int x_pos, int y_pos);
  void draw (CL_Surface& sur, int x_pos, int y_pos, int frame);
  void draw (CL_Surface& sur, int x_pos, int y_pos, 
	     float size_x, float size_y, int frame);


  void draw_line (int x1, int y1, int x2, int y2, 
		  float r, float g, float b, float a = 1.0f);
  void draw_fillrect (int x1, int y1, int x2, int y2, 
		      float r, float g, float b, float a = 1.0f);
  void draw_rect (int x1, int y1, int x2, int y2, 
		  float r, float g, float b, float a = 1.0f);
  void draw_pixel (int x_pos, int y_pos, 
		   float r, float g, float b, float a = 1.0f);
  void draw_circle (int x_pos, int y_pos, int radius,
		   float r, float g, float b, float a = 1.0f);

  bool get_property (ViewProperty p);
  void set_property (ViewProperty p);

  CL_Vector screen_to_world (const CL_Vector&);
  CL_Vector world_to_screen (const CL_Vector&);
};

#endif

/* EOF */
