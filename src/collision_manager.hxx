//  $Id: collision_manager.hxx,v 1.3 2003/05/13 18:28:10 grumbel Exp $
// 
//  Pingus - A free Lemmings clone
//  Copyright (C) 2002 Ingo Ruhnke <grumbel@gmx.de>
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

#ifndef HEADER_FEUERKRAFT_COLLISION_MANAGER_HXX
#define HEADER_FEUERKRAFT_COLLISION_MANAGER_HXX

#include <vector>
#include "math.hxx"

class View;

/** */
class CollisionManager
{
private:
  enum { SHAPE_CIRCLE, SHAPE_RECT }; 

  struct Circle {
    int object_id;
    float x, y;
    float radius;
  };

  struct Rectangle {
    int object_id;
    float x, y;
    float width, height;
    float orientation;
  };

  struct Shape {
    int type;

    union {
      struct Circle    circle;
      struct Rectangle rect;
    };
  };

  typedef std::vector<Shape> Shapes;
  Shapes shapes;

  Math::Quad rect2quad(const Rectangle& rect);

  void check_rect_rect_collision(const Rectangle& rect1, const Rectangle& rect2);
  void check_circle_rect_collision(const Circle& circle, const Rectangle& rect);
  void check_circle_circle_collision(const Circle& circle1, const Circle& circle2);

  static CollisionManager* current_;
public:
  static CollisionManager* current();
  
  CollisionManager();
  
  /** Removes all collisions shapes and starts a new run */
  void clear();

  /** Runs the collision check */
  void run();

  void draw(View* view);

  /** */
  void add_point(int object_id, float x, float y);

  /** */
  void add_circle(int object_id, float x, float y, float radius);

  /** */
  void add_rect(int object_id, float x, float y, float width, float height, float orientation);
};

#endif

/* EOF */
