//  $Id: output_world_builder.cpp,v 1.5 2003/06/03 14:11:22 grumbel Exp $
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

#include "output_world_builder.hpp"

OutputWorldBuilder::OutputWorldBuilder()
{
}

void
OutputWorldBuilder::add_object(const std::string& type, const AList& alist)
{
  std::cout << "OutputWorldBuilder: gameobj: " << type << std::endl;
  print_alist(alist);
}

void
OutputWorldBuilder::add_brush(const std::string& resname, const AList& alist)
{
  std::cout << "OutputWorldBuilder: brush: " << resname << std::endl;
  print_alist(alist);
}

void
OutputWorldBuilder::add_building(const std::string& type, const AList& alist)
{
  std::cout << "OutputWorldBuilder: building: " << type << std::endl;
  print_alist(alist);
}

void
OutputWorldBuilder::add_groundmap(const std::string& type, const AList& alist)
{
  std::cout << "OutputWorldBuilder: groundmap: " << type << std::endl;
  print_alist(alist);
}

void
OutputWorldBuilder::add_script(const std::string& resname)
{
  std::cout << "OutputWorldBuilder: script: " << resname << std::endl;
}

void
OutputWorldBuilder::print_alist(const AList& alist)
{
  for(AList::const_iterator i = alist.begin(); i != alist.end(); ++i)
    {
      std::cout << "  " << i->first << " -> ";
      switch(i->second.type)
        {
        case AList::AL_INT:
          std::cout << i->second.v_int << std::endl;
          break;
        case AList::AL_FLOAT:
          std::cout << i->second.v_float << std::endl;
          break;
        case AList::AL_BOOL:
          std::cout << i->second.v_bool << std::endl;
          break;
        case AList::AL_STRING:
          std::cout << *i->second.v_string << std::endl;
          break;
        case AList::AL_INTVECTOR2D:
          std::cout << "[" << (*i).second.v_int_vector2d.x
                    << ", " << (*i).second.v_int_vector2d.y
                    << "]"
                    << std::endl;
          break;
          /*case AList::AL_FLOATVECTOR2D:
          std::cout << "[" << (*i).second.v_float_vector2d.x
                    << ", " << (*i).second.v_float_vector2d.y
                    << "]"
                    << std::endl;
                    break;*/
        default:
          std::cout << "<unhandled>" << std::endl;
          break;
        }
    }
}

/* EOF */
