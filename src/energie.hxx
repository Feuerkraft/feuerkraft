//  $Id: energie.hxx,v 1.1 2003/04/19 22:39:06 grumbel Exp $
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

#ifndef ENERGIE_HH
#define ENERGIE_HH

#include "boost/dummy_ptr.hpp"
#include "View.hxx"

class Energie
{
private:
  float max_energie;
  float energie;
  unsigned int last_change;

public:
  Energie (int arg_energie);

  void draw (boost::dummy_ptr<View> view, int x_pos, int y_pos);
  operator int () { return int(energie); }

  void operator--() { 
    --energie; 
    last_change = CL_System::get_time ();
  }

  void operator++() {
    ++energie; 
    last_change = CL_System::get_time ();
  }

  void operator+=(int i) { 
    energie += i; 
    last_change = CL_System::get_time ();
  }

  void operator-=(int i) { 
    energie -= i; 
    last_change = CL_System::get_time ();
  }

};

#endif

/* EOF */
