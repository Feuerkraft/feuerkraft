//  $Id: tree_data.cxx,v 1.2 2003/04/19 23:17:52 grumbel Exp $
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

#include "guile.hxx"
#include "tree.hxx"
#include "tree_data.hxx"

TreeData::TreeData (SCM desc)
{
  name = "feuerkraft/tree";

  /* FIXME: This parsing code needs some abstraction, rewriting it
     over and over again is not good */
  while (gh_pair_p (desc))
    {
      if (gh_pair_p (gh_car(desc)))
	{
	  SCM symbol = gh_caar (desc);
	  SCM data   = gh_cdar (desc);
	  
	  if (gh_equal_p (gh_symbol2scm ("pos"), symbol))
	    {
	      // FIXME: No error handling
	      pos.x = gh_scm2double(gh_car (data));
	      pos.y = gh_scm2double(gh_cadr (data));
	    }
	  else
	    {
	      std::cout << "Error: TreeData" << std::endl;
	    }
	}
      else
	{
	  std::cout << "Error: TreeData" << std::endl;
	}
      
      desc = gh_cdr (desc);
    }
}

TreeData::~TreeData ()
{
}

GameObj* 
TreeData::create (boost::dummy_ptr<GameWorld> world)
{
  return new Tree (world, *this);
}

SCM
TreeData::dump_to_scm ()
{
  return SCM_BOOL_F; //scm_listify (gh_symbol2scm ("tree"),
  //Guile::vector2scm (pos),
  //                  SCM_UNDEFINED);
}

/* EOF */
