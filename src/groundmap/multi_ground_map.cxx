//  $Id: multi_ground_map.cxx,v 1.4 2003/06/03 14:11:22 grumbel Exp $
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

#include "multi_ground_map.hxx"

MultiGroundMap::MultiGroundMap (const MultiGroundMapData& data)
  : MultiGroundMapData (data)
{
  for (std::vector<GroundMapData*>::iterator i = mapsdata.begin (); i != mapsdata.end (); ++i)
    {
      maps.push_back ((*i)->create ());
    }
}

MultiGroundMap::~MultiGroundMap ()
{
  for (std::vector<GroundMap*>::iterator i = maps.begin (); i != maps.end (); ++i)
    {
      delete *i;
    }
}

/** Return the type of ground, x and y are in world coordinates */
GroundType
MultiGroundMap::get_groundtype (float x, float y)
{
  for (std::vector<GroundMap*>::reverse_iterator i = maps.rbegin (); i != maps.rend (); ++i)
    {
      GroundType type = (*i)->get_groundtype (x, y);
      if (type != GT_EMPTY)
	return type;
    }  
  return GT_SAND;
}

void
MultiGroundMap::draw(View& view)
{
  for (std::vector<GroundMap*>::reverse_iterator i = maps.rbegin (); i != maps.rend (); ++i)
    {
      (*i)->draw(view);
    }
}

void
MultiGroundMap::draw_levelmap(LevelMap& levelmap)
{
  for (std::vector<GroundMap*>::reverse_iterator i = maps.rbegin (); i != maps.rend (); ++i)
    {
      (*i)->draw_levelmap(levelmap);
    } 
}

void
MultiGroundMap::add (GroundMap* groundmap)
{
  if (groundmap)
    maps.push_back (groundmap);
}

/* EOF */
