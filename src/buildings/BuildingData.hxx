//  $Id: BuildingData.hxx,v 1.1 2002/03/16 23:41:07 grumbel Exp $
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

#ifndef BUILDINGDATA_HXX
#define BUILDINGDATA_HXX

class Building;

class BuildingData
{
protected:
  /** x-Position in the BuildingMap */
  int x_pos;

  /** y-Position in the BuildingMap */
  int y_pos;

public:
  int get_x_pos () { return x_pos; }
  int get_y_pos () { return y_pos; }
  
  /** Returns the width which this building will take on the BuildingMap */
  virtual int map_width () =0;

  /** Returns the height which this building will take on the BuildingMap */
  virtual int map_height () =0;

  virtual Building* create () =0;
};

#endif

/* EOF */
