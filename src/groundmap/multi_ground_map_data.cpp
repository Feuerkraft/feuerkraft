// Feuerkraft - A Tank Battle Game
// Copyright (C) 2000 Ingo Ruhnke <grumbel@gmx.de>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include "multi_ground_map.hpp"
#include "multi_ground_map_data.hpp"

MultiGroundMapData::MultiGroundMapData ()
{
}

MultiGroundMapData::~MultiGroundMapData ()
{
  // FIXME: delete here could be problematic when we copy this class
}

void
MultiGroundMapData::add (GroundMapData* groundmapdata)
{
  mapsdata.push_back (groundmapdata);
}

GroundMap*
MultiGroundMapData::create()
{
  return new MultiGroundMap(*this);
}

/* EOF */
