//  $Id: sexpr_world_reader.cxx,v 1.2 2003/05/11 11:20:44 grumbel Exp $
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

#include "guile.hxx"
#include "world_builder.hxx"
#include "sexpr_world_reader.hxx"

SexprWorldReader::SexprWorldReader(const std::string& arg_filename, 
                                   WorldBuilder* arg_builder)
  : builder(arg_builder)
{
  SCM fdes = scm_open_file (scm_makfrom0str(arg_filename.c_str()),
                            scm_makfrom0str("r"));
  SCM lst  = scm_read (fdes);

  parse_file(lst);
}

SexprWorldReader::SexprWorldReader(SCM data, WorldBuilder* arg_builder)
  : builder(arg_builder)
{
  parse_file(data);
}

void
SexprWorldReader::parse_file(SCM desc)
{
  if (gh_equal_p (gh_symbol2scm ("feuerkraft-scenario"), gh_car(desc)))
    {
      desc = gh_cdr(desc);
    }
  else
    {
      std::cout << "File is not a feuerkraft scenario" << std::endl;
      assert(false);
    }

  while (gh_pair_p(desc))
    {
      if (gh_pair_p (gh_car (desc)))
	{
	  SCM symbol = gh_caar(desc);
	  SCM data   = gh_cdar(desc);   
          
	  if (gh_symbol_p (symbol))
	    {
	      if (gh_equal_p(gh_symbol2scm("groundmap"), symbol))
		{
		  parse_groundmap(data);
		}
	      else if (gh_equal_p(gh_symbol2scm("buildings"), symbol)) 
		{
                  parse_buildings(data);
		}
	      else if (gh_equal_p(gh_symbol2scm("objects"), symbol))
		{
		  parse_objects(data);
		}
	      else if (gh_equal_p(gh_symbol2scm("scripts"), symbol))
		{
		  parse_scripts(data);
		}
	      else
		{
		  std::cout << "GameWorldData: Error: " << symbol << " " << data << std::endl;;
		}
	    }
	  else
	    {
	      std::cout << "GameWorldData: Error not a symbol: ";// << symbol << " " << data << std::endl;;
	      gh_display (symbol); gh_newline ();
	    }
	}
      else
	{
	  std::cout << "GameWorldData: Error not a pair: " << gh_car(desc) << std::endl;;
	}

      desc = gh_cdr(desc);
    }
}

void
SexprWorldReader::parse_buildings(SCM data)
{
  while(!gh_null_p(data))
    {
      SCM building = gh_car(data);
      
      if (gh_symbol_p(gh_car(building)))
        {
          builder->add_building(Guile::symbol2string(gh_car(building)),
                                Guile::scm2alist(gh_cdr(building)));
        }
      else
        {
          std::cout << "SexprWorldReader: Not a building" << std::endl;
          gh_display(building);
          gh_newline();
        }

      data = gh_cdr(data);
    }  
}

void
SexprWorldReader::parse_objects(SCM data)
{
  while(!gh_null_p(data))
    {
      SCM object = gh_car(data);
      
      if (gh_symbol_p(gh_car(object)))
        {
          builder->add_object(Guile::symbol2string(gh_car(object)),
                              Guile::scm2alist(gh_cdr(object)));
        }
      else
        {
          std::cout << "SexprWorldReader: Not a script file:" << std::endl;
          gh_display(object);
          gh_newline();
        }
     
      data = gh_cdr(data);
    }
}

void
SexprWorldReader::parse_brushes(SCM data)
{
  while(!gh_null_p(data))
    {
      
      data = gh_cdr(data);
    }  
}

void
SexprWorldReader::parse_groundmap(SCM data)
{
  while(!gh_null_p(data))
    {
      
      data = gh_cdr(data);
    }  
}

void
SexprWorldReader::parse_scripts(SCM data)
{
  while(!gh_null_p(data))
    {
      SCM script = gh_car(data);
      
      builder->add_script(Guile::scm2string(script));
      
      data = gh_cdr(data);
    }
}

/* EOF */
