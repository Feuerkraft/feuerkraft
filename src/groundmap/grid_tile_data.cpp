//  $Id: grid_tile_data.cpp,v 1.3 2003/06/03 14:11:22 grumbel Exp $
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

#include "grid_tile.hpp"
#include "grid_tile_data.hpp"

GridTile*
GridTileData::create ()
{
  //return new GridTile (*this);
  return 0;// FIXME: Unused
}

static bool Gridless(const GridTileData& a, const GridTileData& b)
{
  if (a.ul < b.ul)
    return true;
  else if (a.ul > b.ul) 
    return false;
  else
    if (a.ur < b.ur)
      return true;
    else if (a.ur > b.ur) 
      return false;    
    else
      if (a.br < b.br)
	return true;
      else if (a.br > b.br) 
	return false;    
      else
	if (a.bl < b.bl)
	  return true;
	else if (a.bl > b.bl) 
	  return false;

  return false;
}

bool operator<(const GridTileData& a, const GridTileData& b)
{
  /*
  std::cout << "if ("  << (int)a.ul << (int)a.ur << (int)a.br  << (int)a.bl
	    << " < " 
	    << (int)b.ul << (int)b.ur << (int)b.br << (int)b.bl
	    << ") != " << Gridless (a, b) << ": " << "print \"Error\""<< std::endl;
  */
  return Gridless (a, b);
}

std::ostream& operator<<(std::ostream& s, const GridTileData& b)
{
  s << "#<GroundType "
    << GroundType2string(b.ul) << ", "
    << GroundType2string(b.ur) << ", "
    << GroundType2string(b.br) << ", "
    << GroundType2string(b.bl)
    << ">";
  return s;
}

bool
GridTileData::operator==(const GridTileData& b)
{
  return (this->ur == b.ur
	  && this->ul == b.ul
	  && this->bl == b.bl
	  && this->br == b.br); 
}

/* EOF */
