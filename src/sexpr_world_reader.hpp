//  $Id: sexpr_world_reader.hpp,v 1.3 2003/06/03 14:11:22 grumbel Exp $
//
//  Feuerkraft - A Tank Battle Game
//  Copyright (C) 2002 Ingo Ruhnke <grumbel@gmx.de>
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.

#ifndef HEADER_SEXPR_WORLD_READER_HXX
#define HEADER_SEXPR_WORLD_READER_HXX

#include <guile/gh.h>
#include <string>

class WorldBuilder;

/** */
class SexprWorldReader
{
private:
  WorldBuilder* builder;
  SCM data;

public:
  SexprWorldReader(const std::string& arg_filename, WorldBuilder* arg_builder);
  SexprWorldReader(SCM data, WorldBuilder* arg_builder);

  void run();
private:
  void parse_file(SCM desc);

  void parse_buildings(SCM data);
  void parse_objects(SCM data);
  void parse_brushes(SCM data);
  void parse_groundmap(SCM data);
  void parse_scripts(SCM data);

  SexprWorldReader (const SexprWorldReader&);
  SexprWorldReader& operator= (const SexprWorldReader&);
};

#endif

/* EOF */
