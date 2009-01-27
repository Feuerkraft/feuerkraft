//  $Id: geometry.hxx,v 1.3 2003/06/03 14:11:22 grumbel Exp $
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

#ifndef GEOMETRY_HH
#define GEOMETRY_HH

#include <math.h>

class Rectangle;
class Line;
class Circle;
class Point;

class Geometry
{
private:
  
public:
  // Dispatcher
  bool do_not_intersec (const Geometry&) =0;

  bool do_not_intersec (const Circle&) =0;
  bool do_not_intersec (const Line&) =0;
  bool do_not_intersec (const Rectangle&) =0;
  bool do_not_intersec (const Point&) =0;
};

class Circle : public Geometry
{
public:
  Circle (double x, double y, double radius);

  bool do_not_intersec (const Geometry& obj) { return obj.do_not_intersec (*this); }

  bool do_not_intersec (const Circle&);
  bool do_not_intersec (const Line&);
  bool do_not_intersec (const Rectangle&);
  bool do_not_intersec (const Point&);

  double get_radius ();
  Point  get_position ();
};

class Rectangle: public Geometry
{
public:
  Rectangle (double x, doubel y, double width, double height, double rotation);

  bool do_not_intersec (const Geometry& obj) { return obj.do_not_intersec (*this); }

  bool do_not_intersec (const Circle&);
  bool do_not_intersec (const Line&);
  bool do_not_intersec (const Rectangle&);
  bool do_not_intersec (const Point&);
};

class Line : public Geometry
{
private:
  double x1, y1;
  double x2, y2;
public:
  Line (double x2, double y2, double x2, double y2);

  bool do_not_intersec (const Geometry& obj) { return obj.do_not_intersec (*this); }

  bool do_not_intersec (const Circle&);
  bool do_not_intersec (const Line&);
  bool do_not_intersec (const Rectangle&);
  bool do_not_intersec (const Point&);

  double get_length ();
};

class Point : public Geometry
{
private:
  double x;
  double y;
public:
  Point (double x, double y);

  bool do_not_intersec (const Geometry& obj) { return obj.do_not_intersec (*this); }

  bool do_not_intersec (const Circle&);
  bool do_not_intersec (const Line&);
  bool do_not_intersec (const Rectangle&);
  bool do_not_intersec (const Point&);

  double get_x () { return x; }
  double get_y () { return y; }
  double distance (Point& p) { 
    return std::fabs(std::sqrt((p.x - x) * (p.x - x) + (p.y - y) * (p.y - y)));
  }
};

#endif

/* EOF */
