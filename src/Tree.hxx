//  $Id: Tree.hxx,v 1.5 2002/04/03 10:55:47 grumbel Exp $
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

#ifndef TREE_HH
#define TREE_HH

#include <string>
#include <ClanLib/core.h>
#include <ClanLib/display2.h>
#include "GameObj.hxx"
#include "TreeData.hxx"

class Tree : public GameObj,
	     public TreeData
{
private:
  CL_Sprite sur;
  CL_Sprite sur_shadow;
public:
  Tree (boost::dummy_ptr<GameWorld>  w, const TreeData& data);
  ~Tree ();
  
  GameObjData* get_data ();
  
  void draw (View* view);
  int get_z_pos () { return 100; }
};

#endif

/* EOF */
