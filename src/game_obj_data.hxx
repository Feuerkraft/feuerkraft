//  $Id: game_obj_data.hxx,v 1.2 2003/05/11 11:20:44 grumbel Exp $
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

#ifndef GAMEOBJDATA_HXX
#define GAMEOBJDATA_HXX

#include <boost/dummy_ptr.hpp>

class GameWorld;
class GameObj;

class GameObjData
{
private:

public:
  /** Create the correct GameObj out of an GameObjData object. This is
      something like a virtual constructor. */
  virtual GameObj* create() =0;
  
  /** Convert the data from a given data object into an SCM which can
      be written to a save game file or similar things */
  virtual SCM dump_to_scm () =0;
};

#endif

/* EOF */
