//  $Id: output_world_builder.hxx,v 1.2 2003/05/11 11:20:44 grumbel Exp $
// 
//  Pingus - A free Lemmings clone
//  Copyright (C) 2002 Ingo Ruhnke <grumbel@gmx.de>
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

#ifndef HEADER_OUTPUT_WORLD_BUILDER_HXX
#define HEADER_OUTPUT_WORLD_BUILDER_HXX

#include <iostream>
#include "world_builder.hxx"

/** */
class OutputWorldBuilder
  : public WorldBuilder
{
public:
  OutputWorldBuilder();

  void add_object(const std::string& type, const AList&);
  void add_brush(const std::string& resname, const AList&);
  void add_building(const std::string&, const AList&);
  void add_groundmap(const std::string&, const AList&);
  void add_script(const std::string& resname);

private:
  void print_alist(const AList& alist);

  OutputWorldBuilder (const OutputWorldBuilder&);
  OutputWorldBuilder& operator= (const OutputWorldBuilder&);
};

#endif

/* EOF */
