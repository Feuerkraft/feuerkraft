//  $Id: collision_manager.cxx,v 1.9 2003/06/18 14:38:28 grumbel Exp $
//
//  Feuerkraft - A Tank Battle Game
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

#include <iostream>
#include <assert.h>
#include <math.h>
#include "math.hxx"
#include "color.hxx"
#include "view.hxx"
#include "game_world.hxx"
#include "buildings/building.hxx"
#include "buildings/building_map.hxx"
#include "collision_manager.hxx"
#include "game_obj_manager.hxx"
#include "display/drawing_context.hxx"

CollisionManager* CollisionManager::current_ = 0;

CollisionManager*
CollisionManager::current()
{
  return current_;
}

CollisionManager::CollisionManager()
{
  current_ = this;
}

void
CollisionManager::clear()
{
  shapes.clear();
}

void
CollisionManager::run()
{
  // Check for GameObj<->GameObj collisions
  for(Shapes::iterator i = shapes.begin(); i != shapes.end(); ++i)
    {
      for(Shapes::iterator j = i + 1; j != shapes.end(); ++j)
        {
          if (i->type == SHAPE_CIRCLE)
            {
              if (j->type == SHAPE_CIRCLE) {
                check_circle_circle_collision(i->circle, j->circle);
              } else if (j->type == SHAPE_RECT) {
                check_circle_rect_collision(i->circle, j->rect);
              }
            }
          else if (i->type == SHAPE_RECT)
            {
              if (j->type == SHAPE_CIRCLE) {
                check_circle_rect_collision(j->circle, i->rect);
              } else if (j->type == SHAPE_RECT) {
                check_rect_rect_collision(i->rect, j->rect);
              }
            }
          else
            {
              assert(false);
            }
        }
    }
  
  // Check for GameObj building collision
  for(Shapes::iterator i = shapes.begin(); i != shapes.end(); ++i)
    {
      switch (i->type)
        {
        case SHAPE_CIRCLE:
          {
            BuildingMap* building_map = GameWorld::current()->get_buildingmap();
            Building* building = building_map->get_building(FloatVector2d(i->circle.x, i->circle.y));
            
            if (!building)
              building = building_map->get_building(FloatVector2d(i->circle.x - i->circle.radius, i->circle.y));

            if (!building)
              building = building_map->get_building(FloatVector2d(i->circle.x + i->circle.radius, i->circle.y));

            if (!building)
              building = building_map->get_building(FloatVector2d(i->circle.x, i->circle.y - i->circle.radius));

            if (!building)
              building = building_map->get_building(FloatVector2d(i->circle.x, i->circle.y + i->circle.radius));
            
            if (building)
              {
                GameObj* obj = GameObjManager::current()->get_object_by_id(i->circle.object_id);
                assert(obj);
                obj->on_collision_with_building(building);
              }
          }
          break;
        case SHAPE_RECT:
          // fixme: not handled
          break;
        default:
          std::cout << "Unhandled type: " << i->type << std::endl;
        }
    }
}

void
CollisionManager::draw(View& view)
{
  for(Shapes::iterator i = shapes.begin(); i != shapes.end(); ++i)
    {
      switch (i->type)
        {
        case SHAPE_CIRCLE:
          view.get_sc().color().draw_circle(i->circle.x, i->circle.y, i->circle.radius,
                                    CL_Color(255, 0, 0));
          break;
        case SHAPE_RECT:
          {
            CL_Color color(255, 0, 0);
            Math::Quad quad = rect2quad(i->rect);
            view.get_sc().color().draw_line(quad.a.x, quad.a.y, quad.b.x, quad.b.y, color);
            view.get_sc().color().draw_line(quad.b.x, quad.b.y, quad.c.x, quad.c.y, color);
            view.get_sc().color().draw_line(quad.c.x, quad.c.y, quad.d.x, quad.d.y, color);
            view.get_sc().color().draw_line(quad.d.x, quad.d.y, quad.a.x, quad.a.y, color);
          }
          break;
        default:
          std::cout << "CollisionManager: unhandled type: " << i->type << std::endl;
        }
    }
}

void
CollisionManager::add_circle(int object_id, float x, float y, float radius)
{
  Shape shape;

  shape.type = SHAPE_CIRCLE;

  shape.circle.object_id = object_id;
  shape.circle.x = x;
  shape.circle.y = y;
  shape.circle.radius = radius;

  shapes.push_back(shape);
}

void
CollisionManager::add_point(int object_id, float x, float y)
{
  add_circle(object_id, x, y, .5f);
}

void
CollisionManager::add_rect(int object_id, float x, float y, float width, float height, float orientation)
{
  Shape shape;
#if 0
  shape.type = SHAPE_RECT;

  shape.rect.object_id = object_id;
  shape.rect.x = x;
  shape.rect.y = y;
  shape.rect.width  = width;
  shape.rect.height = height;
  shape.rect.orientation = orientation;
#else
  shape.type = SHAPE_CIRCLE;
  
  shape.circle.object_id = object_id;
  shape.circle.x = x;
  shape.circle.y = y;
  shape.circle.radius = (width + height)/4;
#endif
  shapes.push_back(shape);
}

Math::Quad
CollisionManager::rect2quad(const Rectangle& rect)
{
  Math::Quad quad;

  float dist = sqrt((rect.width/2) * (rect.width/2) + (rect.height/2) * (rect.height/2));

  float angle = atan2(rect.height/2, rect.width/2);

  // upper/left
  quad.a.x = rect.x + dist * sin(angle - rect.orientation);
  quad.a.y = rect.y + dist * cos(angle - rect.orientation);
  // upper/right
  quad.b.x = rect.x + dist * sin(-angle - rect.orientation);
  quad.b.y = rect.y + dist * cos(-angle - rect.orientation);
  // lower/right
  quad.c.x = rect.x + dist * sin(angle - rect.orientation + Math::pi);
  quad.c.y = rect.y + dist * cos(angle - rect.orientation + Math::pi);
  // lower/left
  quad.d.x = rect.x + dist * sin(-angle - rect.orientation + Math::pi);
  quad.d.y = rect.y + dist * cos(-angle - rect.orientation + Math::pi);

  return quad;
}

void
CollisionManager::check_rect_rect_collision(const Rectangle& rect1, const Rectangle& rect2)
{
  if (Math::quad_collide(rect2quad(rect1), rect2quad(rect2)))
    {
      GameObj* obj1 = GameObjManager::current()->get_object_by_id(rect1.object_id);
      GameObj* obj2 = GameObjManager::current()->get_object_by_id(rect2.object_id);

      assert(obj1);
      assert(obj2);

      obj1->on_collision(obj2);
      obj2->on_collision(obj1);
    }
}

void
CollisionManager::check_circle_rect_collision(const Circle& circle, const Rectangle& rect)
{
  
}

void
CollisionManager::check_circle_circle_collision(const Circle& circle1, const Circle& circle2)
{
  float a = circle2.x - circle1.x;
  float b = circle2.y - circle1.y;
  float dist = sqrt(a*a + b*b);

  if (dist < circle1.radius + circle2.radius)
    {
      GameObj* obj1 = GameObjManager::current()->get_object_by_id(circle1.object_id);
      GameObj* obj2 = GameObjManager::current()->get_object_by_id(circle2.object_id);

      assert(obj1);
      assert(obj2);

      obj1->on_collision(obj2);
      obj2->on_collision(obj1);
    }
}

/* EOF */
