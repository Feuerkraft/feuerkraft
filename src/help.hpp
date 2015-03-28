//  $Id: help.hpp,v 1.1 2003/06/05 21:34:23 grumbel Exp $
//
//  Pingus - A free Lemmings clone
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

#ifndef HEADER_HELP_HXX
#define HEADER_HELP_HXX

#include <ClanLib/Display/font.h>
#include "gui_obj.hpp"

/** */
class Help : public GuiObj
{
private:
  CL_Font font;
public:
  Help();
  ~Help();

  void draw(CL_GraphicContext& gc);
  void update(float delta);
private:
  Help (const Help&);
  Help& operator= (const Help&);
};

#endif

/* EOF */
