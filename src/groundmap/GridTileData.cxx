//  $Id: GridTileData.cxx,v 1.2 2002/03/25 15:32:58 grumbel Exp $
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

#include "GridTile.hxx"
#include "GridTileData.hxx"

GridTile*
GridTileData::create ()
{
  //return new GridTile (*this);
  return 0;// FIXME: Unused
}

bool operator<(const GridTileData& a, const GridTileData& b)
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

/* EOF */
