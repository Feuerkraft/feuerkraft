// Feuerkraft - A Tank Battle Game
// Copyright (C) 2002 Ingo Ruhnke <grumbel@gmail.com>
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

#include <assert.h>
#include "guile.hpp"
#include "world_builder.hpp"
#include "sexpr_world_reader.hpp"

SexprWorldReader::SexprWorldReader(const std::string& arg_filename,
                                   WorldBuilder* arg_builder)
  : builder(arg_builder)
{
  SCM fdes = scm_open_file (scm_from_utf8_string(arg_filename.c_str()),
                            scm_from_utf8_string("r"));
  SCM lst  = scm_read (fdes);

  data = lst;

  scm_close(fdes);
}

SexprWorldReader::SexprWorldReader(SCM arg_data, WorldBuilder* arg_builder)
  : builder(arg_builder),
    data(arg_data)
{
}

void
SexprWorldReader::run()
{
  parse_file(data);
}

void
SexprWorldReader::parse_file(SCM desc)
{
  if (scm_equal_p (scm_from_utf8_symbol("feuerkraft-scenario"), scm_car(desc)))
    {
      desc = scm_cdr(desc);
    }
  else
    {
      std::cout << "File is not a feuerkraft scenario" << std::endl;
      assert(false);
    }

  while (scm_pair_p(desc))
    {
      if (scm_pair_p (scm_car (desc)))
	{
	  SCM symbol = scm_caar(desc);
	  SCM data   = scm_cdar(desc);

	  if (scm_symbol_p (symbol))
	    {
	      if (scm_equal_p(scm_from_utf8_symbol("groundmap"), symbol))
		{
		  parse_groundmap(data);
		}
	      else if (scm_equal_p(scm_from_utf8_symbol("buildings"), symbol))
		{
                  parse_buildings(data);
		}
	      else if (scm_equal_p(scm_from_utf8_symbol("objects"), symbol))
		{
		  parse_objects(data);
		}
	      else if (scm_equal_p(scm_from_utf8_symbol("scripts"), symbol))
		{
		  parse_scripts(data);
		}
	      else
		{
		  std::cout << "Error: " << symbol << " " << data << std::endl;;
		}
	    }
	  else
	    {
	      std::cout << "Error not a symbol: ";// << symbol << " " << data << std::endl;;
	      scm_display(symbol, SCM_UNDEFINED);
              scm_newline(SCM_UNDEFINED);
	    }
	}
      else
	{
	  std::cout << "Error not a pair: " << scm_car(desc) << std::endl;;
	}

      desc = scm_cdr(desc);
    }
}

void
SexprWorldReader::parse_buildings(SCM data)
{
  while(!scm_null_p(data))
    {
      SCM building = scm_car(data);

      if (scm_symbol_p(scm_car(building)))
        {
          builder->add_building(Guile::symbol2string(scm_car(building)),
                                Guile::scm2alist(scm_cdr(building)));
        }
      else
        {
          std::cout << "SexprWorldReader: Not a building" << std::endl;
          scm_display(building, SCM_UNDEFINED);
          scm_newline(SCM_UNDEFINED);
        }

      data = scm_cdr(data);
    }
}

void
SexprWorldReader::parse_objects(SCM data)
{
  while(!scm_null_p(data))
    {
      SCM object = scm_car(data);

      if (scm_symbol_p(scm_car(object)))
        {
          builder->add_object(Guile::symbol2string(scm_car(object)),
                              Guile::scm2alist(scm_cdr(object)));
        }
      else
        {
          std::cout << "SexprWorldReader: Not a script file:" << std::endl;
          scm_display(object, SCM_UNDEFINED);
          scm_newline(SCM_UNDEFINED);
        }

      data = scm_cdr(data);
    }
}

void
SexprWorldReader::parse_brushes(SCM data)
{
  while(!scm_null_p(data))
    {

      data = scm_cdr(data);
    }
}

void
SexprWorldReader::parse_groundmap(SCM data)
{
  while(!scm_null_p(data))
    {

      data = scm_cdr(data);
    }
}

void
SexprWorldReader::parse_scripts(SCM data)
{
  while(!scm_null_p(data))
    {
      SCM script = scm_car(data);

      builder->add_script(Guile::scm2string(script));

      data = scm_cdr(data);
    }
}

/* EOF */
