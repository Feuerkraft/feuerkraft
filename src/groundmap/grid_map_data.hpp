// Feuerkraft - A Tank Battle Game
// Copyright (C) 2000 Ingo Ruhnke <grumbel@gmail.com>
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

#ifndef GRIDMAPDATA_HXX
#define GRIDMAPDATA_HXX

#include <vector>
#include "scheme_compat.hpp"
#include "ground_type.hpp"
#include "ground_map_data.hpp"

/**
 */
class GridMapData : public GroundMapData
{
protected:
  int grid_width;
  int grid_height;

  /** The data of the grid */
  std::vector<GroundType> grid_data;

public:
  GridMapData (SCM desc);
  virtual ~GridMapData ();

  GroundMap* create ();
private:
  void parse_from_file (SCM desc);
};

#endif

/* EOF */
