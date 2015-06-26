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

#ifndef GAMEWORLDDATA_HXX
#define GAMEWORLDDATA_HXX

#include <libguile.h>
#include <vector>
#include <string>

class GameObjData;
class GroundMapData;
class BuildingMapData;
class GameWorld;

class GameWorldData
{
protected:
  bool needs_delete;
  std::vector<GameObjData*> gameobj_data;
  std::vector<std::string> scripts;
  GroundMapData* groundmap_data;
  BuildingMapData* buildingmap_data;

public:
  explicit GameWorldData (SCM desc);
  virtual ~GameWorldData ();

  /** Convert the data from a given data object into an SCM which can
      be written to a save game file or similar things */
  SCM dump_to_scm ();

private:
  void parse_objects(SCM desc);
  void parse_scripts(SCM desc);

private:
  GameWorldData(const GameWorldData&);
  GameWorldData& operator=(const GameWorldData&);
};

#endif

/* EOF */
