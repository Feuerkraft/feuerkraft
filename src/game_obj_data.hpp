//  $Id: game_obj_data.hpp,v 1.4 2003/06/03 14:11:22 grumbel Exp $
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

#ifndef GAMEOBJDATA_HXX
#define GAMEOBJDATA_HXX

class GameWorld;
class GameObj;

class GameObjData
{
private:

public:
  virtual ~GameObjData() {}

  /** Create the correct GameObj out of an GameObjData object. This is
      something like a virtual constructor. */
  virtual GameObj* create() =0;
  
  /** Convert the data from a given data object into an SCM which can
      be written to a save game file or similar things */
  virtual SCM dump_to_scm () =0;
};

#endif

/* EOF */
