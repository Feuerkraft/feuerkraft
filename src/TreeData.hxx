//  $Id: TreeData.hxx,v 1.2 2002/04/03 10:55:47 grumbel Exp $
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

#ifndef TREEDATA_HXX
#define TREEDATA_HXX

#include <string>
#include <ClanLib/core.h>
#include <guile/gh.h>
#include "GameObjData.hxx"

class TreeData : public GameObjData
{
protected:
  CL_Vector pos;
  std::string name;
  // FIXME: Insert destruction status here

public:
  /** Formate: (tree (pos 100 100))*/
  TreeData (SCM desc);
  virtual ~TreeData ();

  GameObj* create (boost::dummy_ptr<GameWorld> world);
  SCM dump_to_scm ();
};

#endif

/* EOF */
