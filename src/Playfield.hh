//  $Id: Playfield.hh,v 1.2 2001/05/01 15:06:52 grumbel Exp $
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

#ifndef PLAYFIELD_HH
#define PLAYFIELD_HH

#include "GameObj.hh"

class Playfield : public GameObj
{
private:

public:
  Playfield (boost::dummy_ptr<GameWorld>  w);
  virtual ~Playfield () {}

  void draw (View*);
  void update (float){}
  int get_z_pos () { return -1; }
};

#endif

/* EOF */
