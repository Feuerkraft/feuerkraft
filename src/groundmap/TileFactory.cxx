//  $Id: TileFactory.cxx,v 1.1 2002/03/06 21:50:39 grumbel Exp $
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

#include <iostream>

#include "TileData.hxx"
#include "SpriteTileData.hxx"
#include "SpriteTile.hxx"
#include "TileFactory.hxx"

TileData*
TileFactory::create (SCM desc)
{
  SCM symbol = gh_car (desc);
  SCM data   = gh_cdr (desc);
  
  if (gh_equal_p (gh_symbol2scm ("spritetile"), symbol))
    {
      return create_SpriteTile (data);
    }
  else
    {
      std::cout << "TileFactory: Unknown tile type: '" << std::flush;
      gh_display (symbol);
      std::cout << "' with data: " << std::flush;
      gh_display (data);
      std::cout << std::endl;
      return 0;
    }
}

SpriteTileData*
TileFactory::create_SpriteTile (SCM desc)
{
  SpriteTileData sprite_data;

  while (!gh_null_p (desc))
    {
      SCM symbol = gh_caar(desc);
      SCM data   = gh_cdr(desc);

      if (gh_equal_p (gh_symbol2scm ("width"), symbol))
	{
	  sprite_data.width = gh_scm2int(gh_car (data));
	}
      else if (gh_equal_p (gh_symbol2scm ("height"), symbol))
	{
	  sprite_data.height = gh_scm2int(gh_car (data));
	}
      else if (gh_equal_p (gh_symbol2scm ("sprite"), symbol))
	{
	  char* str = gh_scm2newstr(gh_car (data), 0);
	  sprite_data.sprite_location = str;
	  free (str);
	}
      else
	{
	  std::cout << "TileFactory: Unknown sprite tile type: '" << std::flush;
	  gh_display (symbol);
	  std::cout << "' with data: " << std::flush;
	  gh_display (data);
	  std::cout << std::endl;
	  return 0;
	}

      desc = gh_cdr (desc);
    }

  return new SpriteTile (sprite_data);
}

/* EOF */
