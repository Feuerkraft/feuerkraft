//  $Id: GridTileGenerator.hxx,v 1.2 2002/03/26 12:51:33 grumbel Exp $
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

#ifndef GRIDTILEGENERATOR_HXX
#define GRIDTILEGENERATOR_HXX

#include <vector>
#include <map>
#include <string>
#include <guile/gh.h>
#include "GroundType.hxx"
#include "GridTileData.hxx"

/** Creates/loads the tiles for a GridMap out of an description */
class GridTileGenerator
{
private:

public:
  typedef std::pair<GridTileData, std::vector<GridTile*> > TileTableEntry;
  typedef std::vector<std::pair<GridTileData, std::vector<GridTile*> > > TileTable;
  TileTable tiles;

  GridTileGenerator (std::string filename);
  ~GridTileGenerator ();

  GridTile* create (const GridTileData& data);
private:
  GroundType symbol2GroundType (SCM);
  void parse_line (SCM desc);
  GridTileData scm2GridTileData (SCM);
  std::vector<GridTile*> scm2GridTileVector (SCM);
};

#endif

/* EOF */
